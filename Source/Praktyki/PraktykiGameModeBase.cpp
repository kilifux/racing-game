// Fill out your copyright notice in the Description page of Project Settings.

#include "PraktykiGameModeBase.h"
#include "Car.h"
#include "CarPlayerController.h"
#include "GameInstanceBase.h"
#include "Kismet/GameplayStatics.h"

void APraktykiGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Car = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	CarPlayerController = Cast<ACarPlayerController>(GetWorld()->GetFirstPlayerController());
	GameInstanceBase = GetGameInstance<UGameInstanceBase>();
	Laps = GameInstanceBase->GetLaps();
	//GetWorld()->GetTimerManager().SetTimer(TimeLeftTimerHandle, this, &APraktykiGameModeBase::CheckTimeLeft, 0.1f, true);
}

void APraktykiGameModeBase::PlayerCrossedFinishLine()
{
	if (Car->GetCurrentLap() == Laps && CarPlayerController != nullptr)
	{
		CarPlayerController->GameHasEnded(Car, true);
	}
}

void APraktykiGameModeBase::CheckTimeLeft()
{
	if (Car->GetTimeLeft() <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimeLeftTimerHandle);
		CarPlayerController->GameHasEnded(Car, false);
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


