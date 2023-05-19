// Copyright 2023 Teyon. All Rights Reserved.


#include "MainMenuWidget.h"
#include "GameInstanceBase.h"
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

	GameInstanceBase = GetGameInstance<UGameInstanceBase>();
	
	LapSlider->OnValueChanged.AddDynamic(this, &UMainMenuWidget::GetLapSliderValue);
	MaxTimeSlider->OnValueChanged.AddDynamic(this, &UMainMenuWidget::GetMaxTimeValue);
	ModeSlider->OnValueChanged.AddDynamic(this, &UMainMenuWidget::GetModeValue);

	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::StartLevel);
	ModifyCarButton->OnClicked.AddDynamic(this, &UMainMenuWidget::StartModifyMenu);
	
	LapSliderText->SetVisibility(ESlateVisibility::Hidden);
	LapSlider->SetVisibility(ESlateVisibility::Hidden);
	GameInstanceBase->SetLaps(1);
	GameInstanceBase->SetMaxTime(30);
	GameInstanceBase->SetMode(1);
}

FString UMainMenuWidget::TimeToFormat(float TimeToFormat)
{
	Minutes = FMath::FloorToInt(TimeToFormat / 60);
	Seconds = FMath::FloorToInt(FMath::Fmod(TimeToFormat, 60));

	return FString::Printf(TEXT("%d:%02d"), Minutes, Seconds);
}

void UMainMenuWidget::GetLapSliderValue(float Value)
{
	GameInstanceBase->SetLaps(Value);	
	LapSliderText->SetText(FText::FromString(FString::FromInt(Value)));
}

void UMainMenuWidget::GetMaxTimeValue(float Value)
{
	GameInstanceBase->SetMaxTime(Value);
	MaxTimeText->SetText(FText::FromString(TimeToFormat(Value)));
}

void UMainMenuWidget::GetModeValue(float Value)
{
	GameInstanceBase->SetMode(Value);
	if (Value == 1)
	{
		ModeText->SetText(FText::FromString("Practice"));
		GameInstanceBase->SetLaps(1);
		LapSliderText->SetVisibility(ESlateVisibility::Hidden);
		LapSlider->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (Value == 2)
	{
		ModeText->SetText(FText::FromString("Race"));
		LapSliderText->SetVisibility(ESlateVisibility::Visible);
		LapSlider->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainMenuWidget::StartLevel()
{
	UGameplayStatics::OpenLevel(this, FName("TestMap"));
}

void UMainMenuWidget::StartModifyMenu()
{
	UGameplayStatics::OpenLevel(this, FName("ModifyMap"));
}
