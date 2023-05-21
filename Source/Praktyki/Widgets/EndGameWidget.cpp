// Copyright 2023 Teyon. All Rights Reserved.


#include "EndGameWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

UEndGameWidget::UEndGameWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UEndGameWidget::RestartLevel);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UEndGameWidget::ExitLevel);
	}
}

FString UEndGameWidget::TimeToFormat(float TimeToFormat)
{
	Minutes = FMath::FloorToInt(TimeToFormat / 60);
	Seconds = FMath::FloorToInt(FMath::Fmod(TimeToFormat, 60));
	Milliseconds = FMath::FloorToInt((TimeToFormat - FMath::Floor(TimeToFormat)) * 1000);

	return FString::Printf(TEXT("%d:%02d.%03d"), Minutes, Seconds, Milliseconds);
}

void UEndGameWidget::SetTableResults(int Index, float BestLapTime, float FinalTime)
{
	TXTTableResults->SetText(FText::FromString(FString::FromInt(Index) + TimeToFormat(BestLapTime).LeftPad(38) + TimeToFormat(FinalTime).LeftPad(38)));
}

void UEndGameWidget::SetTableLaps(TArray<float> LapTimes, TArray<float> DeltaTimes)
{
	FString CurrentText = TXTTableLaps->GetText().ToString();
	FString NewLine;
	
	if(LapTimes.Num() > 0)
	{
		for (int i = 0; i < LapTimes.Num(); i++)
		{
			if (DeltaTimes[i] > 0)
			{
				NewLine = FString::Printf(TEXT("%u.%s-%s\n"), i + 1, *TimeToFormat(LapTimes[i]).LeftPad(40).RightPad(65), *TimeToFormat(abs(DeltaTimes[i])));
			}
			else
			{
				NewLine = FString::Printf(TEXT("%u.%s+%s\n"), i + 1, *TimeToFormat(LapTimes[i]).LeftPad(40).RightPad(65), *TimeToFormat(abs(DeltaTimes[i])));
			}
			CurrentText += NewLine;
			TXTTableLaps->SetText(FText::FromString(CurrentText));
		}
	}
}

void UEndGameWidget::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void UEndGameWidget::ExitLevel()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}
