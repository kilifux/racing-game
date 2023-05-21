// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PraktykiGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API APraktykiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	int Laps;
	float MaxTime;
	int Mode;
	
	class ACar* Car;
	class ACarPlayerController* CarPlayerController;
	class UGameInstanceBase* GameInstanceBase;

public:
	
	int GetLaps() const;

	void SetLaps(const int InLaps);

	void PlayerCrossedFinishLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
