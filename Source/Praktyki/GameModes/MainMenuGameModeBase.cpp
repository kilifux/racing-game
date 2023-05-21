// Copyright 2023 Teyon. All Rights Reserved.


#include "MainMenuGameModeBase.h"
#include "Praktyki/Widgets/MainMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
	
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
