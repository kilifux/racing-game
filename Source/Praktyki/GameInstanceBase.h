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

	int FrontHoodIndex;
	int MainBodyIndex;
	int FrontBumperIndex;
	int RearBumperIndex;
	int RearBootIndex;

public:
	
	int GetLaps() const;
	void SetLaps(const int NewLaps);
	int GetMode() const;
	void SetMode(const int NewMode);
	float GetMaxTime() const;
	void SetMaxTime(const float NewMaxTime);
	
	int GetFrontHoodIndex() const;
	void SetFrontHoodIndex(const int NewFrontHoodIndex);
	int GetMainBodyIndex() const;
	void SetMainBodyIndex(const int NewMainBodyIndex);
	int GetFrontBumperIndex() const;
	void SetFrontBumperIndex(const int NewFrontBumperIndex);
	int GetRearBumperIndex() const;
	void SetRearBumperIndex(const int NewRearBumperIndex);
	int GetRearBootIndex() const;
	void SetRearBootIndex(const int NewRearBootIndex);
};
