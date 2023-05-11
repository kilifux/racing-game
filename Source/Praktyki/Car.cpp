// Copyright 2023 Teyon. All Rights Reserved.


#include "Car.h"
#include "Camera/CameraComponent.h"
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
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	
	SpringArmInteriorComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Interior Component"));
	SpringArmInteriorComponent->SetupAttachment(SkeletalMeshComponent, TEXT("CarInteriorGameplayCamera"));
	SpringArmInteriorComponent->TargetArmLength = 35.f;

	CameraInteriorComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Interior Component"));
	CameraInteriorComponent->SetupAttachment(SpringArmInteriorComponent, USpringArmComponent::SocketName);
	CameraInteriorComponent->SetAutoActivate(false);
	
	SpringArmExteriorComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Exterior Component"));
	SpringArmExteriorComponent->SetupAttachment(SkeletalMeshComponent, TEXT("BehindCarReverseInteriorCamera"));

	CameraExteriorComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Exterior Component"));
	CameraExteriorComponent->SetupAttachment(SpringArmExteriorComponent, USpringArmComponent::SocketName);

	WheelBackLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Back Left"));
	WheelBackLeft->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_back_left_spin"));
	
	WheelBackRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Back Right"));
	WheelBackRight->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_back_right_spin"));
	
	WheelFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Front Left"));
	WheelFrontLeft->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_front_left_spin"));
	
	WheelFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Front Right"));
	WheelFrontRight->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_front_right_spin"));

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Steering Wheel"));
	SteeringWheel->SetupAttachment(SkeletalMeshComponent);

	MaxSpeed = 2000;
	Acceleration = 800000;
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
	UE_LOG(LogTemp, Warning, TEXT("Current velocity: %f"), GetVelocity().Length());
	//HandleSideDrag();
	//CounterTorque();
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
	float Speed = Velocity.Size();
	if (Speed <= 0.1f)
	{
		SkeletalMeshComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
		return;
	}
    
	// Obliczenie kierunku hamowania
	FVector BrakeDirection = -Velocity.GetSafeNormal();
    
	// Dodanie siły hamującej do komponentu fizyki pojazdu
	FVector BrakeForceVector = BrakeDirection * BrakeForce * 1.5f;
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
	FVector SuspensionForce = GetSuspensionForce();
	float SuspensionForceZ = SuspensionForce.Z;
	float NormalizedSpeed = Speed / MaxSpeed;
	FVector BrakeDirection = -GetVelocity().GetSafeNormal();
	float SkidFactor = FMath::Clamp(1.0f - SuspensionForceZ / SkidThreshold, 0.0f, 1.0f);
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

	// Ograniczenie siły hamowania w przypadku skręcania
	float BrakeForceLimited = 100 * FMath::Clamp(1.0f - FMath::Abs(SteeringAngle) / 80, 0.0f, 1.0f);

	// Dodanie siły hamującej do komponentu fizyki pojazdu
	FVector BrakeForceVector = BrakeDirection * BrakeForceLimited;
	SkeletalMeshComponent->AddForce(BrakeForceVector);

	// Dodanie siły oporu bocznego w celu zapobiegania skręcaniu w drifty
	if (GetVelocity().Length() > 200)
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


FVector ACar::GetSuspensionForce()
{
	// Ustaw długość i kierunek raya
	float TraceLength = 50;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart - FVector(0.0f, 0.0f, TraceLength);

	// Wykonaj ray tracing
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("SuspensionTrace")), true, this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldStatic, TraceParams))
	{
		// Oblicz siłę reakcji podłoża na podstawie siły grawitacji i normalnej powierzchni kolizji
		float GravityMagnitude = GetWorld()->GetGravityZ() * SkeletalMeshComponent->GetMass();
		FVector GravityForce = FVector(0.0f, 0.0f, GravityMagnitude);
		FVector NormalForce = -HitResult.Normal * FVector::DotProduct(GravityForce, -HitResult.Normal);
		return NormalForce;
	}

	return FVector::ZeroVector;
}


