// Copyright 2023 Teyon. All Rights Reserved.


#include "Car.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	WheelBackLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Back Left"));
	WheelBackLeft->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_back_left_spin"));
	
	WheelBackRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Back Right"));
	WheelBackRight->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_back_right_spin"));

	WheelFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Front Left"));
	WheelFrontLeft->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_front_left_spin"));

	WheelFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Front Right"));
	WheelFrontRight->SetupAttachment(SkeletalMeshComponent, TEXT("wheel_front_right_spin"));

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

