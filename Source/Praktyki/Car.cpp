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
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	//SkeletalMeshComponent->SetCollisionProfileName("PhysicsActor");

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
	//WheelBackLeft->SetCollisionProfileName("PhysicsActor");
	
	WheelBackRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Back Right"));
	WheelBackRight->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_back_right_spin"));
	//WheelBackRight->SetCollisionProfileName("PhysicsActor");
	
	WheelFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Front Left"));
	WheelFrontLeft->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_front_left_spin"));
	//WheelFrontLeft->SetCollisionProfileName("PhysicsActor");
	
	WheelFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Front Right"));
	WheelFrontRight->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_front_right_spin"));
	//WheelFrontRight->SetCollisionProfileName("PhysicsActor");

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Steering Wheel"));
	SteeringWheel->SetupAttachment(SkeletalMeshComponent);
	
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
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
	FVector2D ThrottleAxisVector = Value.Get<FVector2D>();
	FVector ForceToAdd(50000000.f, 0.f, 0.f);
	SkeletalMeshComponent->AddForce(GetActorForwardVector() * ForceToAdd * ThrottleAxisVector.X * GetWorld()->GetDeltaSeconds());
	
}

void ACar::Break(const FInputActionValue& Value)
{
	FVector2D ThrottleAxisVector = Value.Get<FVector2D>();
	FVector ForceToAdd(58000000.f, 0.f, 0.f);
	
	SkeletalMeshComponent->AddForce(-GetActorForwardVector() * ForceToAdd * ThrottleAxisVector.X * GetWorld()->GetDeltaSeconds());
}

void ACar::Steering(const FInputActionValue& Value)
{
	float SteeringAxis = Value.Get<float>();
	FVector Torque = FVector(0.f, 0.f, 200.f) * SteeringAxis;
	SkeletalMeshComponent->AddTorqueInRadians(GetActorUpVector() * Torque * GetWorld()->GetDeltaSeconds(), NAME_None, true);
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

