// Copyright 2023 Teyon. All Rights Reserved.


#include "ModifyMenuWidget.h"
#include "CarModel.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "GameInstanceBase.h"
#include "Kismet/GameplayStatics.h"

UModifyMenuWidget::UModifyMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UModifyMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstanceBase = GetGameInstance<UGameInstanceBase>();
	CarModel = Cast<ACarModel>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	FrontHoodSlider->OnValueChanged.AddDynamic(this, &UModifyMenuWidget::GetFrontHoodSliderValue);
	MainBodySlider->OnValueChanged.AddDynamic(this, &UModifyMenuWidget::GetMainBodySliderValue);
	FrontBumperSlider->OnValueChanged.AddDynamic(this, &UModifyMenuWidget::GetFrontBumperSliderValue);
	RearBumperSlider->OnValueChanged.AddDynamic(this, &UModifyMenuWidget::GetRearBumperSliderValue);
	RearBootSlider->OnValueChanged.AddDynamic(this, &UModifyMenuWidget::GetRearBootSliderValue);
	OthersSlider->OnValueChanged.AddDynamic(this, &UModifyMenuWidget::GetOthersSliderValue);

	ExitButton->OnClicked.AddDynamic(this,&UModifyMenuWidget::ExitLevel);

	FrontHoodSlider->SetValue(GameInstanceBase->GetFrontHoodIndex());
	MainBodySlider->SetValue(GameInstanceBase->GetMainBodyIndex());
	FrontBumperSlider->SetValue(GameInstanceBase->GetFrontBumperIndex());
	RearBumperSlider->SetValue(GameInstanceBase->GetRearBumperIndex());
	RearBootSlider->SetValue(GameInstanceBase->GetRearBootIndex());
	OthersSlider->SetValue(GameInstanceBase->GetOthersIndex());
}

void UModifyMenuWidget::GetFrontHoodSliderValue(float Value)
{
	GameInstanceBase->SetFrontHoodIndex(Value);
	CarModel->SetMaterialFrontHood(Value);
}

void UModifyMenuWidget::GetMainBodySliderValue(float Value)
{
	GameInstanceBase->SetMainBodyIndex(Value);
	CarModel->SetMaterialMainBody(Value);
}

void UModifyMenuWidget::GetFrontBumperSliderValue(float Value)
{
	GameInstanceBase->SetFrontBumperIndex(Value);
	CarModel->SetMaterialFrontBumper(Value);
}

void UModifyMenuWidget::GetRearBumperSliderValue(float Value)
{
	GameInstanceBase->SetRearBumperIndex(Value);
	CarModel->SetMaterialFrontBumper(Value);
}

void UModifyMenuWidget::GetRearBootSliderValue(float Value)
{
	GameInstanceBase->SetRearBootIndex(Value);
	CarModel->SetMaterialRearBoot(Value);
}

void UModifyMenuWidget::GetOthersSliderValue(float Value)
{
	GameInstanceBase->SetOthersIndex(Value);
	CarModel->SetMaterialOthers(Value);
}

void UModifyMenuWidget::ExitLevel()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}
