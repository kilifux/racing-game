// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API UGameManager : public UObject
{
	GENERATED_BODY()

	int Laps;

public:
	int GetLaps() const;
	void SetLaps(const int NewLaps);
};
