// Copyright 2023 Teyon. All Rights Reserved.


#include "FinishLine.h"

#include "Car.h"
#include "CarPlayerController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(BoxComponent);

	LeftPole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Pole"));
	LeftPole->SetupAttachment(BoxComponent);

	RightPole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Pole"));
	RightPole->SetupAttachment(BoxComponent);
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnCapsuleBeginOverlap);

	Car = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	CarPlayerController = Cast<ACarPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
}

void AFinishLine::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ACar>())
	{
		CarPlayerController->AddLap();
		UE_LOG(LogTemp, Warning, TEXT("DOTKANLES MNIE! Lap: %u"), CarPlayerController->GetCurrentLap());
	}
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

