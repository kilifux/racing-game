// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CarPlayerController.generated.h"

class UUserWidget;

UCLASS()
class PRAKTYKI_API ACarPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UUserWidget* HUDUserWidget;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
