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

	bEndGame = false;
}

void ACarPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UEndGameWidget* EndGameWidget = Cast<UEndGameWidget>(CreateWidget(this, EndGameWidgetClass));
	if (EndGameWidget != nullptr)
	{
		bEndGame = true;
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;
		
		if(InGameHUD != nullptr)
		{
			InGameHUD->RemoveWidget();
		}
		
		if (bIsWinner)
		{
			EndGameWidget->SetTableResults(0, Car->GetBestTime(), GetGameTimeSinceCreation());
			EndGameWidget->SetTableLaps(Car->GetLapTimes(), Car->GetDeltaTimes());
			Car->SetActorTickEnabled(false);
		}
		else
		{
			EndGameWidget->SetTableResults(0, 0, 0);
			EndGameWidget->SetTableLaps(Car->GetLapTimes(), Car->GetDeltaTimes());
			Car->SetActorTickEnabled(false);
		}
		
		EndGameWidget->AddToViewport();
		
		if (Car != nullptr)
		{
			Car->DetachFromControllerPendingDestroy();
		}
	}
	
}

bool ACarPlayerController::IsEndGame() const
{
	return bEndGame;
}






