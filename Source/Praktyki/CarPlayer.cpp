// Copyright 2023 Teyon. All Rights Reserved.


#include "CarPlayer.h"
#include "CarPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameInstanceBase.h"
#include "EnhancedInputSubsystems.h"
#include "InGameHUD.h"

ACarPlayer::ACarPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	bTimeExpired = false;
}

void ACarPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	GetWorld()->GetTimerManager().SetTimer(CurrentVelocityTimerHandle, this, &ACarPlayer::SetCurrentSpeed, 0.1f, true);
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

	SetMaterialFrontBumper(GameInstanceBase->GetFrontBumperIndex());
	SetMaterialFrontHood(GameInstanceBase->GetFrontHoodIndex());
	SetMaterialMainBody(GameInstanceBase->GetMainBodyIndex());
	SetMaterialRearBoot(GameInstanceBase->GetRearBootIndex());
	SetMaterialRearBumper(GameInstanceBase->GetRearBumperIndex());
}

void ACarPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (TimeLeft <= 0 && !bTimeExpired)
	{
		PlayerController->GameHasEnded(this, false);
		bTimeExpired = true;
		GetWorld()->GetTimerManager().PauseTimer(CurrentVelocityTimerHandle);
		return;
	}
	
	TimeLeft = MaxTime - CurrentTime;
	InGameHUD->UpdateCurrentTimeText(CurrentTime, LastTime);
	InGameHUD->UpdateMaxTime(TimeLeft);
}

void ACarPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Started, this, &ACarPlayer::ToggleCamera);
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ACarPlayer::LookAround);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ACar::Throttle);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ACar::Steering);
	}
}

void ACarPlayer::LookAround(const FInputActionValue& Value)
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
		float NewYaw = FMath::Clamp(CurrentRotation.Yaw + LookAxisVector.X, -50.0f, 50.0f);
		SpringArmExteriorComponent->SetRelativeRotation(FRotator(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll));
	}
}

void ACarPlayer::ToggleCamera()
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

void ACarPlayer::SetCurrentSpeed()
{
	CurrentSpeed = GetVelocity().Length();
	
	if (InGameHUD != nullptr && !PlayerController->IsEndGame())
	{
		InGameHUD->UpdateCurrenSpeedText(GetCurrentSpeed());
	}
}

void ACarPlayer::AddLap()
{
	Super::AddLap();
	
	if (InGameHUD)
	{
		InGameHUD->UpdateTable(LapTimes.Num(), LastTime, DeltaTimes.Last());
		InGameHUD->UpdateBestLastTimeText(BestTime, LastTime);
	}
}




