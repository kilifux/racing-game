// Copyright 2023 Teyon. All Rights Reserved.


#include "PlayerWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

UPlayerWidget::UPlayerWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	 
}

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FString UPlayerWidget::TimeToFormat(float TimeToFormat)
{
	Minutes = FMath::FloorToInt(TimeToFormat / 60);
	Seconds = FMath::FloorToInt(FMath::Fmod(TimeToFormat, 60));
	Milliseconds = FMath::FloorToInt((TimeToFormat - FMath::Floor(TimeToFormat)) * 1000);

	return FString::Printf(TEXT("%d:%02d.%03d"), Minutes, Seconds, Milliseconds);
}

void UPlayerWidget::UpdateMaxTime(float Value)
{
	TXTMaxTime->SetText(FText::FromString(TimeToFormat(Value)));
}

void UPlayerWidget::UpdateMode(FString Mode)
{
	TXTMode->SetText(FText::FromString(Mode));
}

void UPlayerWidget::UpdateCurrentSpeedText(int Value)
{
	TXTCurrentSpeed->SetText(FText::FromString(FString::FromInt(Value) + " KM/H"));
}

void UPlayerWidget::UpdateLapsText(int CurrentLap, int Laps)
{
	TXTLaps->SetText(FText::FromString(FString::FromInt(CurrentLap) + "/" + FString::FromInt(Laps)));
}

void UPlayerWidget::UpdateCurrentTimeText(float RaceTime, float LapTime)
{
	TXTCurrentTime->SetText(FText::FromString("TIME" + TimeToFormat(RaceTime).LeftPad(21) + "\nLAP TIME \t " + TimeToFormat(LapTime)));
}

void UPlayerWidget::UpdateBestLastTimeText(float BestTime, float LastTime)
{
	TXTBestLastTime->SetText(FText::FromString("BEST  " + TimeToFormat(BestTime).LeftPad(15) + "\nLAST  " + TimeToFormat(LastTime).LeftPad(15)));
}

void UPlayerWidget::UpdateTable(int LapIndex, float Time, float DeltaBest)
{
	FString CurrentText = TXTTable->GetText().ToString();
	FString NewLine;
	if (DeltaBest > 0)
	{
		NewLine = FString::Printf(TEXT("%d.%s-%s\n"), LapIndex, *TimeToFormat(Time).LeftPad(15).RightPad(22), *TimeToFormat(abs(DeltaBest)));
	}
	else
	{
		NewLine = FString::Printf(TEXT("%d.%s+%s\n"), LapIndex, *TimeToFormat(Time).LeftPad(15).RightPad(22), *TimeToFormat(abs(DeltaBest)));
	}
	
	CurrentText += NewLine;
	TXTTable->SetText(FText::FromString(CurrentText));
}
