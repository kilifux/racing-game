// Copyright 2023 Teyon. All Rights Reserved.


#include "Car.h"
#include "InGameHUD.h"
#include "CarPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameInstanceBase.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SetRootComponent(SkeletalMeshComponent);
	
	SpringArmInteriorComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Interior Component"));
	SpringArmInteriorComponent->SetupAttachment(SkeletalMeshComponent, TEXT("CarInteriorGameplayCamera"));
	SpringArmInteriorComponent->TargetArmLength = 20.f;

	CameraInteriorComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Interior Component"));
	CameraInteriorComponent->SetupAttachment(SpringArmInteriorComponent, USpringArmComponent::SocketName);
	CameraInteriorComponent->SetAutoActivate(false);
	
	SpringArmExteriorComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Exterior Component"));
	SpringArmExteriorComponent->SetupAttachment(SkeletalMeshComponent, TEXT("BehindCarReverseInteriorCamera"));

	CameraExteriorComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Exterior Component"));
	CameraExteriorComponent->SetupAttachment(SpringArmExteriorComponent, USpringArmComponent::SocketName);

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Steering Wheel"));
	SteeringWheel->SetupAttachment(SkeletalMeshComponent);

	MaxSpeed = 2350;
	Acceleration = 1700000;
	SteeringSensitivity = 5000;
	MaxAngularSpeed = 50;
	SkidThreshold = 0.3f;
	bTimeExpired = false;
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<ACarPlayerController>(Controller);
	
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	GetWorld()->GetTimerManager().SetTimer(CurrentVelocityTimerHandle, this, &ACar::SetCurrentSpeed, 0.1f, true);
	InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	GameInstanceBase = GetGameInstance<UGameInstanceBase>();
	
	MaxTime = GameInstanceBase->GetMaxTime();

	InGameHUD->UpdateLapsText(CurrentLap, GameInstanceBase->GetLaps());
	
	if (GameInstanceBase->GetMode() == 1)
	{
		InGameHUD->UpdateMode(TEXT("PRACTICE"));
	}
	else
	{
		InGameHUD->UpdateMode(TEXT("RACE"));
	}
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (TimeLeft <= 0 && !bTimeExpired)
	{
		PlayerController->GameHasEnded(this, false);
		bTimeExpired = true;
		GetWorld()->GetTimerManager().PauseTimer(CurrentVelocityTimerHandle);
		return;
	}
	
	CurrentTime = PlayerController->GetGameTimeSinceCreation();
	LastTime = PlayerController->GetGameTimeSinceCreation() - LapTime;
	TimeLeft = MaxTime - CurrentTime;

	InGameHUD->UpdateCurrentTimeText(CurrentTime, LastTime);
	InGameHUD->UpdateMaxTime(TimeLeft);
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Started, this, &ACar::ToggleCamera);
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ACar::LookAround);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ACar::Throttle);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ACar::Steering);
	}
}

void ACar::AddLap()
{
	CurrentLap += 1;
	if (PlayerController)
	{
		LapTime = PlayerController->GetGameTimeSinceCreation();;
	}
	
	LapTimes.Add(LastTime);
	LapTimes.Sort();
	
	if (InGameHUD)
	{
		InGameHUD->UpdateTable(LapTimes.Num(), LastTime, BestTime - LastTime);
		BestTime = LapTimes[0];
		InGameHUD->UpdateBestLastTimeText(BestTime, LastTime);
	}
}

void ACar::SetCurrentSpeed()
{
	CurrentSpeed = GetVelocity().Length();
	
	if (InGameHUD != nullptr && !PlayerController->IsEndGame())
	{
		InGameHUD->UpdateCurrenSpeedText(GetCurrentSpeed());
	}
}

void ACar::LookAround(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

		if (CameraInteriorComponent->IsActive() && !CameraExteriorComponent->IsActive())
		{
			FRotator CurrentRotation = SpringArmInteriorComponent->GetRelativeRotation();
			float NewYaw = FMath::Clamp(CurrentRotation.Yaw + LookAxisVector.X, -45.0f, 45.0f);
			SpringArmInteriorComponent->SetRelativeRotation(FRotator(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll));
		}
		else if (CameraExteriorComponent->IsActive() && !CameraInteriorComponent->IsActive())
		{
			FRotator CurrentRotation = SpringArmExteriorComponent->GetRelativeRotation();
			float NewYaw = FMath::Clamp(CurrentRotation.Yaw + LookAxisVector.X, -35.0f, 35.0f);
			SpringArmExteriorComponent->SetRelativeRotation(FRotator(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll));
		}
}

void ACar::Throttle(const FInputActionValue& Value)
{
	ThrottleAxisVector = Value.Get<FVector>();

	if (ThrottleAxisVector.X <= 0)
	{
		ThrottleAxisVector.X /= 1.5;
	}

	SkeletalMeshComponent->AddForce(GetActorForwardVector() * ThrottleAxisVector.X * Acceleration);
	CurrentVelocity = SkeletalMeshComponent->GetPhysicsLinearVelocity();
	
	if (CurrentVelocity.Length() > MaxSpeed)
	{
		SkeletalMeshComponent->SetPhysicsLinearVelocity(CurrentVelocity.GetSafeNormal() * MaxSpeed);
	}
}

void ACar::Steering(const FInputActionValue& Value)
{
	SteeringAxisVector = Value.Get<FVector>();
	
	// Calculate the steering angle based on the input value and SteeringSensitivity
	float SteeringAngle = SteeringAxisVector.X * SteeringSensitivity;

	// Calculate the value of the turning force
	float SteeringForce = SteeringAngle * SteeringSensitivity;

	// Check the direction of vehicle movement and invert the sign of the turning force if it is moving in reverse
	FVector Velocity = SkeletalMeshComponent->GetPhysicsLinearVelocity();
	float Speed = Velocity.Size();
	FVector ForwardVector = GetActorForwardVector();
	float DotProduct = FVector::DotProduct(Velocity.GetSafeNormal(), ForwardVector);
	if (DotProduct < 0)
	{
		SteeringForce *= -1;
	}
	
	float NormalizedSpeed = Speed / MaxSpeed;
	float SteeringForceLimited = SteeringForce * NormalizedSpeed;
	FVector TorqueVector = FVector(0.0f, 0.0f, SteeringForceLimited);
	
	SkeletalMeshComponent->AddTorqueInRadians(TorqueVector);
}

void ACar::ToggleCamera()
{
	CameraInteriorComponent->Deactivate();
	CameraExteriorComponent->Deactivate();

	if (Choose)
	{
		CameraInteriorComponent->Activate();
		Choose = false;
	}
	else
	{
		CameraExteriorComponent->Activate();
		Choose = true;
	}
}




