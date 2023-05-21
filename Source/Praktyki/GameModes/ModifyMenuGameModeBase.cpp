// Copyright 2023 Teyon. All Rights Reserved.


#include "ModifyMenuGameModeBase.h"
#include "Praktyki/Cars/CarModel.h"
#include "Praktyki/Widgets/ModifyMenuWidget.h"
#include "Kismet/GameplayStatics.h"


void AModifyMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CarModel = Cast<ACarModel>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
	
	if (ModifyMenuWidgetClass)
	{
		ModifyMenuWidget = CreateWidget<UModifyMenuWidget>(GetWorld(), ModifyMenuWidgetClass);

		if (ModifyMenuWidget)
		{
			ModifyMenuWidget->AddToViewport();
		}
	}
	
}
