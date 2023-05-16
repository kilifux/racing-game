// Copyright 2023 Teyon. All Rights Reserved.


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LapSlider->OnValueChanged.AddDynamic(this, &UMainMenuWidget::GetLapSliderValue);
	MaxTimeSlider->OnValueChanged.AddDynamic(this, &UMainMenuWidget::GetMaxTimeValue);
	ModeSlider->OnValueChanged.AddDynamic(this, &UMainMenuWidget::GetModeValue);

	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::StartLevel);
	
}

FString UMainMenuWidget::TimeToFormat(float TimeToFormat)
{
	Minutes = FMath::FloorToInt(TimeToFormat / 60);
	Seconds = FMath::FloorToInt(FMath::Fmod(TimeToFormat, 60));

	return FString::Printf(TEXT("%d:%02d"), Minutes, Seconds);
}

void UMainMenuWidget::GetLapSliderValue(float Value)
{
	Laps = Value;
	LapSliderText->SetText(FText::FromString(FString::FromInt(Value)));
}

void UMainMenuWidget::GetMaxTimeValue(float Value)
{
	MaxTime = Value;
	MaxTimeText->SetText(FText::FromString(TimeToFormat(Value)));
}

void UMainMenuWidget::GetModeValue(float Value)
{
	Mode = Value;
	if (Value == 1)
	{
		ModeText->SetText(FText::FromString("Practice"));
	}
	else if (Value == 2)
	{
		ModeText->SetText(FText::FromString("Race"));
	}
	
}

void UMainMenuWidget::StartLevel()
{
	UGameplayStatics::OpenLevel(this, FName("TestMap"));
}

float UMainMenuWidget::GetMaxTime() const
{
	return MaxTime;
}

int UMainMenuWidget::GetMode() const
{
	return Mode;
}

int UMainMenuWidget::GetLaps() const
{
	return Laps;
}
