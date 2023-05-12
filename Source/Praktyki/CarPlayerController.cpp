// Copyright 2023 Teyon. All Rights Reserved.


#include "CarPlayerController.h"
#include "Blueprint/UserWidget.h"

void ACarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDUserWidget = CreateWidget(this, HUDWidgetClass);
	HUDUserWidget->AddToViewport();
	
	Laps = 1;
	CurrentLap = 0;

	Time = FDateTime::UtcNow();
}


int ACarPlayerController::GetLaps() const
{
	return Laps;
}

void ACarPlayerController::SetLaps(const int InLaps)
{
	Laps = InLaps;
}

int ACarPlayerController::GetCurrentLap() const
{
	return CurrentLap;
}

void ACarPlayerController::SetCurrentLap(const int InCurrentLap)
{
	CurrentLap = InCurrentLap;
}

void ACarPlayerController::AddLap()
{
	CurrentLap += 1;
}
