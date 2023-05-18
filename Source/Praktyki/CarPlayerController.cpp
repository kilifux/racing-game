// Copyright 2023 Teyon. All Rights Reserved.

#include "CarPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Car.h"
#include "EndGameWidget.h"
#include "InGameHUD.h"
#include "Kismet/GameplayStatics.h"

void ACarPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//EndGameWidget = Cast<UEndGameWidget>(CreateWidget(this, EndGameWidgetClass));
	Car = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void ACarPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UEndGameWidget* EndGameWidget = Cast<UEndGameWidget>(CreateWidget(this, EndGameWidgetClass));
	if (EndGameWidget)
	{
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;
		
		if(InGameHUD)
		{
			InGameHUD->RemoveWidget();
		}
		
		if (bIsWinner)
		{
			EndGameWidget->SetTableResults(0, Car->GetBestTime(), GetGameTimeSinceCreation());
		}
		else
		{
			EndGameWidget->SetTableResults(0, 0, 0);
		}
		
		EndGameWidget->AddToViewport();
		if (Car)
		{
			Car->DetachFromControllerPendingDestroy();
		}
	}
	
}





