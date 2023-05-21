// Fill out your copyright notice in the Description page of Project Settings.

#include "PraktykiGameModeBase.h"
#include "Praktyki/Cars/Car.h"
#include "Praktyki/Player/CarPlayerController.h"
#include "Praktyki/GameInstanceBase.h"
#include "Kismet/GameplayStatics.h"

void APraktykiGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	Car = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	CarPlayerController = Cast<ACarPlayerController>(GetWorld()->GetFirstPlayerController());
	GameInstanceBase = GetGameInstance<UGameInstanceBase>();
	Laps = GameInstanceBase->GetLaps();
}

void APraktykiGameModeBase::PlayerCrossedFinishLine()
{
	if (Car && CarPlayerController)
	{
		if (Car->GetCurrentLap() == Laps)
		{
			CarPlayerController->GameHasEnded(Car, true);
		}
	}
}

int APraktykiGameModeBase::GetLaps() const
{
	return Laps;
}

void APraktykiGameModeBase::SetLaps(const int InLaps)
{
	Laps = InLaps;
}


