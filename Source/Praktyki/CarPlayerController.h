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
	TSubclassOf<UUserWidget> EndGameWidgetClass;

	class UEndGameWidget* EndGameWidget;
	
	class AInGameHUD* InGameHUD;
	
	class ACar* Car;

public:
	int GetLaps() const;
	void SetLaps(const int NewLaps);
	float GetMaxTime() const;
	void SetMaxTime(const float NewMaxTime);
	int GetMode() const;
	void SetMode(const int NewMode);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;
	
	
};
