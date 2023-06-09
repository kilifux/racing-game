// Copyright 2023 Teyon. All Rights Reserved.

#include "CarPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Praktyki/Cars/Car.h"
#include "Praktyki/Widgets/EndGameWidget.h"
#include "Praktyki/Widgets/InGameHUD.h"
#include "Kismet/GameplayStatics.h"


void ACarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Car = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	bEndGame = false;
}

void ACarPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UEndGameWidget* EndGameWidget = Cast<UEndGameWidget>(CreateWidget(this, EndGameWidgetClass));
	
	if (EndGameWidget)
	{
		bEndGame = true;
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;
		
		if(InGameHUD)
		{
			InGameHUD->RemoveWidget();
		}
		
		if (bIsWinner)
		{
			EndGameWidget->SetTableResults(1, Car->GetBestTime(), GetGameTimeSinceCreation());
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
		
		if (Car)
		{
			Car->DetachFromControllerPendingDestroy();
		}
	}
}

bool ACarPlayerController::IsEndGame() const
{
	return bEndGame;
}






