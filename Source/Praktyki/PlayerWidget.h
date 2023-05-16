// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UTextBlock;
class UBorder;

UCLASS()
class PRAKTYKI_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TXTCurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TXTLaps;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TXTCurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TXTBestLastTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UBorder* TableBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* TXTTable;
	
	int Minutes;
	int Seconds;
	int Milliseconds;

	FWidgetTransform WidgetTransform;

	
public:
	UPlayerWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	FString TimeToFormat(float TimeToFormat);

	void UpdateCurrentSpeedText(int Value);
	void UpdateLapsText(int CurrentLap, int Laps);
	void UpdateCurrentTimeText(float RaceTime, float LapTime);
	void UpdateBestLastTimeText(float BestTime, float LastTime);
	void UpdateTable(int LapIndex, float Time, float DeltaBest);
};
