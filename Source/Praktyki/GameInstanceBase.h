// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API UGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

	int Laps;
	int Mode;
	float MaxTime;

public:
	int GetLaps() const;
	void SetLaps(const int NewLaps);
	int GetMode() const;
	void SetMode(const int NewMode);
	float GetMaxTime() const;
	void SetMaxTime(const float NewMaxTime);
};
