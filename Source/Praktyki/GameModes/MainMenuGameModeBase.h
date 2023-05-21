// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	class UMainMenuWidget* MainMenuWidget;

	APlayerController* PlayerController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
