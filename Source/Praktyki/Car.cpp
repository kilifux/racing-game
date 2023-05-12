// Copyright 2023 Teyon. All Rights Reserved.


#include "Car.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
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

	MaxSpeed = 2200;
	Acceleration = 1250000;
	SteeringSensitivity = 5000;
	MaxAngularSpeed = 50;
	SkidThreshold = 0.3f;
	
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);
	
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Display, TEXT("Velocity: %f"), GetVelocity().Length());
	//UE_LOG(LogTemp, Warning, TEXT("Current velocity: %f"), GetVelocity().Length());
	
	
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
		EnhancedInputComponent->BindAction(BreakAction, ETriggerEvent::Triggered, this, &ACar::Break);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ACar::Steering);

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

	FVector ForwardForce = GetActorForwardVector() * ThrottleAxisVector.X * Acceleration;
	SkeletalMeshComponent->AddForce(ForwardForce);

	CurrentVelocity = SkeletalMeshComponent->GetPhysicsLinearVelocity();
	
	if (CurrentVelocity.Length() > MaxSpeed)
	{
		SkeletalMeshComponent->SetPhysicsLinearVelocity(CurrentVelocity.GetSafeNormal() * MaxSpeed);
	}
}

void ACar::Break(const FInputActionValue& Value)
{
	ThrottleAxisVector = Value.Get<FVector>();
	// Obliczenie siły hamowania w zależności od wartości wejściowej i parametrów pojazdu
	float BrakeForce = ThrottleAxisVector.X * Acceleration;
    
	// Sprawdzenie czy samochód porusza się i czy jest możliwe jego zatrzymanie
	FVector Velocity = SkeletalMeshComponent->GetPhysicsLinearVelocity();
	
	// Obliczenie kierunku hamowania
	FVector BrakeDirection = -Velocity.GetSafeNormal();
    
	// Dodanie siły hamującej do komponentu fizyki pojazdu
	FVector BrakeForceVector = BrakeDirection * BrakeForce * 1.1f;
	SkeletalMeshComponent->AddForce(BrakeForceVector);
}

void ACar::Steering(const FInputActionValue& Value)
{
	FVector SteeringVector = Value.Get<FVector>();
	float SteeringAxis = SteeringVector.X;
	
	// Obliczenie kąta skrętu w zależności od wartości wejściowej i parametrów pojazdu
	float SteeringAngle = SteeringAxis * SteeringSensitivity;

	// Obliczenie wartości siły skręcającej w zależności od kąta skrętu i parametrów pojazdu
	float SteeringForce = SteeringAngle * SteeringSensitivity;

	// Sprawdzenie kierunku ruchu pojazdu i odwrócenie znaku siły skręcającej, jeśli porusza się on wstecz
	FVector Velocity = SkeletalMeshComponent->GetPhysicsLinearVelocity();
	float Speed = Velocity.Size();
	FVector ForwardVector = GetActorForwardVector();
	float DotProduct = FVector::DotProduct(Velocity.GetSafeNormal(), ForwardVector);
	if (DotProduct < 0)
	{
		SteeringForce *= -1;
	}

	// Ograniczenie siły skręcającej w przypadku utraty przyczepności lub przeskakiwania
	float NormalizedSpeed = Speed / MaxSpeed;
	float SkidFactor = FMath::Clamp(1.0f / SkidThreshold, 0.0f, 1.0f);
	float SteeringReductionFactor = FMath::Lerp(1.0f, SkidFactor, 0.5);
	float SteeringForceLimited = SteeringForce * NormalizedSpeed * SteeringReductionFactor;
    
	// Dodanie siły skręcającej do komponentu fizyki pojazdu
	FVector TorqueVector = FVector(0.0f, 0.0f, SteeringForceLimited);
	SkeletalMeshComponent->AddTorqueInRadians(TorqueVector);

	// Ograniczenie prędkości kątowej pojazdu do wartości maksymalnej
	FVector AngularVelocity = SkeletalMeshComponent->GetPhysicsAngularVelocityInRadians();
	if (AngularVelocity.Z > MaxAngularSpeed)
	{
		AngularVelocity.Z = MaxAngularSpeed;
		SkeletalMeshComponent->SetPhysicsAngularVelocityInRadians(AngularVelocity);
	}
	else if (AngularVelocity.Z < -MaxAngularSpeed)
	{
		AngularVelocity.Z = -MaxAngularSpeed;
		SkeletalMeshComponent->SetPhysicsAngularVelocityInRadians(AngularVelocity);
	}
	
	// Dodanie siły oporu bocznego w celu zapobiegania skręcaniu w drifty
	if (GetVelocity().Length() > 50)
	{
		FVector SideDragForce = -GetActorRightVector() * 100000;
		SkeletalMeshComponent->AddForce(SideDragForce);	
	}
	else
	{
		// Ustawienie prędkości kątowej na 0 stopni na sekundę
		SkeletalMeshComponent->SetAllPhysicsAngularVelocityInDegrees(FVector((0.f, 0.f, 0.f)));
	}

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

	UE_LOG(LogTemp, Display, TEXT("Zmieniles kamere"));
	
}

void ACar::Handbrake()
{
	
}



