// Copyright 2023 Teyon. All Rights Reserved.


#include "CarModel.h"
#include "GameInstanceBase.h"

// Sets default values
ACarModel::ACarModel()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SetRootComponent(SkeletalMeshComponent);
	
	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Steering Wheel"));
	SteeringWheel->SetupAttachment(SkeletalMeshComponent);
	
	RearSpoiler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rear Spoiler"));
	RearSpoiler->SetupAttachment(SkeletalMeshComponent, TEXT("spoiler_back"));

	SeatNetClamps = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Seat Net Clamps"));
	SeatNetClamps->SetupAttachment(SkeletalMeshComponent, TEXT("SK_Porsche_911_GT3_R_Bone"));
	
	WingMirrorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing Mirror Left"));
	WingMirrorLeft->SetupAttachment(SkeletalMeshComponent, TEXT("wing_mirror_left"));

	WingMirrorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing Mirror Right"));
	WingMirrorRight->SetupAttachment(SkeletalMeshComponent, TEXT("wing_mirror_right"));

	CockpitConsole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cockpit Console"));
	CockpitConsole->SetupAttachment(SkeletalMeshComponent);
	
	Net = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Net"));
	Net->SetupAttachment(SkeletalMeshComponent);
	
	ExteriorInteriorWindows = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exterior Interior Windows"));
	ExteriorInteriorWindows->SetupAttachment(SkeletalMeshComponent);
	
	EngineComponents = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Engine Components"));
	EngineComponents->SetupAttachment(SkeletalMeshComponent);
	
	WheelRightFront = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Right Front"));
	WheelRightFront->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_front_right_spin"));
	
	WheelRightRear = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Right Rear"));
	WheelRightRear->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_back_right_spin"));
	
	WheelLeftFront = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Left Front"));
	WheelLeftFront->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_front_left_spin"));
	
	WheelLeftRear = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Left Rear"));
	WheelLeftRear->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_back_left_spin"));
	
	RearDiffuser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rear Diffuser"));
	RearDiffuser->SetupAttachment(SkeletalMeshComponent, TEXT("diffuser_back"));
	
	FenderLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fender Left"));
	FenderLeft->SetupAttachment(SkeletalMeshComponent, TEXT("fender_left"));
	
	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Left"));
	DoorLeft->SetupAttachment(SkeletalMeshComponent, TEXT("door_left"));

	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Right"));
	DoorRight->SetupAttachment(SkeletalMeshComponent, TEXT("door_right"));
	
	FenderRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fender Right"));
	FenderRight->SetupAttachment(SkeletalMeshComponent, TEXT("fender_right"));
	
	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rear Bumper"));
	RearBumper->SetupAttachment(SkeletalMeshComponent, TEXT("bumper_rear"));
	
	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Bumper"));
	FrontBumper->SetupAttachment(SkeletalMeshComponent, TEXT("bumper_front"));
	
	FrontHood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Hood"));
	FrontHood->SetupAttachment(SkeletalMeshComponent, TEXT("hood_front"));
	
	Interior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interior"));
	Interior->SetupAttachment(SkeletalMeshComponent, TEXT("SK_Porsche_911_GT3_R_Bone"));
	
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	MainBody->SetupAttachment(SkeletalMeshComponent, TEXT("SK_Porsche_911_Gt3_R1"));
	
	
	RearBoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rear Boot"));
	RearBoot->SetupAttachment(SkeletalMeshComponent, TEXT("boot_rear"));
	
}

// Called when the game starts or when spawned
void ACarModel::BeginPlay()
{
	Super::BeginPlay();

	GameInstanceBase = GetGameInstance<UGameInstanceBase>();
	FrontHood->SetMaterial(0, Materials[GameInstanceBase->GetFrontHoodIndex()]);
	MainBody->SetMaterial(0, Materials[GameInstanceBase->GetMainBodyIndex()]);
	FrontBumper->SetMaterial(0, Materials[GameInstanceBase->GetFrontBumperIndex()]);
	RearBumper->SetMaterial(0, Materials[GameInstanceBase->GetRearBumperIndex()]);
	RearBoot->SetMaterial(0, Materials[GameInstanceBase->GetRearBootIndex()]);
}

// Called every frame
void ACarModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACarModel::SetMaterialFrontHood(float Index)
{
	FrontHood->SetMaterial(0, Materials[Index]);
}

void ACarModel::SetMaterialMainBody(float Index)
{
	MainBody->SetMaterial(0, Materials[Index]);
}

void ACarModel::SetMaterialFrontBumper(float Index)
{
	FrontBumper->SetMaterial(0, Materials[Index]);
}

void ACarModel::SetMaterialRearBumper(float Index)
{
	RearBumper->SetMaterial(0, Materials[Index]);
}

void ACarModel::SetMaterialRearBoot(float Index)
{
	RearBoot->SetMaterial(0, Materials[Index]);
}



