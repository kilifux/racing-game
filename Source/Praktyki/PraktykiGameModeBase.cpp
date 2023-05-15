// Fill out your copyright notice in the Description page of Project Settings.


#include "PraktykiGameModeBase.h"
#include "Car.h"
#include "Kismet/GameplayStatics.h"


void APraktykiGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Car = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Laps = 2;
}


void APraktykiGameModeBase::PlayerCrossedFinishLine()
{
	if (Car->GetCurrentLap() == Laps)
	{
		UE_LOG(LogTemp, Warning, TEXT("Koniec Gry"));
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


