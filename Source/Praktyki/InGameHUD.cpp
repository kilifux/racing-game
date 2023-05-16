// Copyright 2023 Teyon. All Rights Reserved.


#include "InGameHUD.h"
#include "PlayerWidget.h"

AInGameHUD::AInGameHUD()
{
	
}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
		if (PlayerWidget)
		{
			PlayerWidget->AddToViewport();
		}
	}
}

void AInGameHUD::UpdateCurrenSpeedText(int Value)
{
	if (PlayerWidget)
	{
		PlayerWidget->UpdateCurrentSpeedText(Value);
	}
}

void AInGameHUD::UpdateLapsText(int CurrentLap, int Laps)
{
	if (PlayerWidget)
	{
		PlayerWidget->UpdateLapsText(CurrentLap, Laps);
	}
}

void AInGameHUD::UpdateCurrentTimeText(float RaceTime, float LapTime)
{
	if (PlayerWidget)
	{
		PlayerWidget->UpdateCurrentTimeText(RaceTime,LapTime);
	}
}

void AInGameHUD::UpdateBestLastTimeText(float BestTime, float LastTime)
{
	if (PlayerWidget)
	{
		PlayerWidget->UpdateBestLastTimeText(BestTime, LastTime);
	}
}

void AInGameHUD::UpdateTable(int LapIndex, float Time, float DeltaBest)
{
	if (PlayerWidget)
	{
		PlayerWidget->UpdateTable(LapIndex, Time, DeltaBest);
	}
}
