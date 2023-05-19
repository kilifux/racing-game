// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ModifyMenuGameModeBase.generated.h"

UCLASS()
class PRAKTYKI_API AModifyMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UUserWidget> ModifyMenuWidgetClass;

	class UModifyMenuWidget* ModifyMenuWidget;
	
	APlayerController* PlayerController;
	class ACarModel* CarModel;

public:
	virtual void BeginPlay() override;
};
