// Copyright 2023 Teyon. All Rights Reserved.


#include "EndGameWidget.h"
#include "Components/Border.h"
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
		RestartButton->OnClicked.AddDynamic(this,&UEndGameWidget::RestartLevel);
	}
}

void UEndGameWidget::SetTableResults(int Index, float BestLapTime, float FinalTime)
{
	if (TXTTableResults)
	{
		TXTTableResults->SetText(FText::FromString(FString::FromInt(Index) + "\t\t\t\t\t\t\t\t\t\t" + TimeToFormat(BestLapTime) + "\t\t\t\t\t\t\t\t\t\t" + TimeToFormat(FinalTime)));
	}
	
}

FString UEndGameWidget::TimeToFormat(float TimeToFormat)
{
	Minutes = FMath::FloorToInt(TimeToFormat / 60);
	Seconds = FMath::FloorToInt(FMath::Fmod(TimeToFormat, 60));
	Milliseconds = FMath::FloorToInt((TimeToFormat - FMath::Floor(TimeToFormat)) * 1000);

	return FString::Printf(TEXT("%d:%02d.%03d"), Minutes, Seconds, Milliseconds);
}

void UEndGameWidget::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, "TestMap");
}
