// Fill out your copyright notice in the Description page of Project Settings.


#include "PraktykiGameModeBase.h"
#include "Car.h"
#include "CarPlayerController.h"
#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"


void APraktykiGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Car = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	CarPlayerController = Cast<ACarPlayerController>(GetWorld()->GetFirstPlayerController());
}


void APraktykiGameModeBase::PlayerCrossedFinishLine()
{
	if (Car->GetCurrentLap() == Laps)
	{
		CarPlayerController->GameHasEnded(Car, true);
		Car->DetachFromControllerPendingDestroy();
		
		
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


