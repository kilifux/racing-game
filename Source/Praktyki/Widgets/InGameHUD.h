// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	class UPlayerWidget* PlayerWidget;
public:
	AInGameHUD();
	
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	void RemoveWidget();
	
	void UpdateCurrenSpeedText(int Value);

	void UpdateLapsText(int CurrentLap, int Laps);

	void UpdateCurrentTimeText(float RaceTime, float LapTime);

	void UpdateBestLastTimeText(float BestTime, float LastTime);

	void UpdateTable(int LapIndex, float Time, float DeltaBest);
	
	void UpdateMaxTime(float Value);

	void UpdateMode(FString Mode);
};



