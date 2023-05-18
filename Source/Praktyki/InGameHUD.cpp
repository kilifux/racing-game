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

	if (PlayerWidgetClass != nullptr)
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
		if (PlayerWidget != nullptr)
		{
			PlayerWidget->AddToViewport();
		}
	}
}

void AInGameHUD::RemoveWidget()
{
	if (PlayerWidget != nullptr)
	{
		PlayerWidget->RemoveFromParent();
		PlayerWidget->Destruct();
	}
}

void AInGameHUD::UpdateCurrenSpeedText(int Value)
{
	if (PlayerWidget != nullptr)
	{
		PlayerWidget->UpdateCurrentSpeedText(Value);
	}
}

void AInGameHUD::UpdateLapsText(int CurrentLap, int Laps)
{
	if (PlayerWidget != nullptr)
	{
		PlayerWidget->UpdateLapsText(CurrentLap, Laps);
	}
}

void AInGameHUD::UpdateCurrentTimeText(float RaceTime, float LapTime)
{
	if (PlayerWidget != nullptr)
	{
		PlayerWidget->UpdateCurrentTimeText(RaceTime,LapTime);
	}
}

void AInGameHUD::UpdateBestLastTimeText(float BestTime, float LastTime)
{
	if (PlayerWidget != nullptr)
	{
		PlayerWidget->UpdateBestLastTimeText(BestTime, LastTime);
	}
}

void AInGameHUD::UpdateTable(int LapIndex, float Time, float DeltaBest)
{
	if (PlayerWidget != nullptr)
	{
		PlayerWidget->UpdateTable(LapIndex, Time, DeltaBest);
	}
}

void AInGameHUD::UpdateMaxTime(float Value)
{
	if (PlayerWidget != nullptr)
	{
		PlayerWidget->UpdateMaxTime(Value);
	}
}

void AInGameHUD::UpdateMode(FString Mode)
{
	if (PlayerWidget != nullptr)
	{
		PlayerWidget->UpdateMode(Mode);
	}
}
