// Copyright 2023 Teyon. All Rights Reserved.

#include "FinishLine.h"
#include "Praktyki/Cars/Car.h"
#include "Praktyki/Widgets/InGameHUD.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Praktyki/GameModes/PraktykiGameModeBase.h"
#include "NiagaraActor.h"
#include "Praktyki/Player/CarPlayer.h"

// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	PraktykiGameModeBase = Cast<APraktykiGameModeBase>(GetWorld()->GetAuthGameMode());
	InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void AFinishLine::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ACar>() && PraktykiGameModeBase)
	{
		Car->AddLap();

		if (OtherActor->IsA<ACarPlayer>())
		{
			PraktykiGameModeBase->PlayerCrossedFinishLine();
			if (InGameHUD && Car)
			{
				InGameHUD->UpdateLapsText(Car->GetCurrentLap(), PraktykiGameModeBase->GetLaps());
			}

			if ((Car->GetCurrentLap() + 1) == PraktykiGameModeBase->GetLaps())
			{
				GetWorld()->SpawnActor<ANiagaraActor>(FinishEffect, GetActorLocation(), GetActorRotation());
			}
		}
	}
}

