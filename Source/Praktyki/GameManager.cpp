// Copyright 2023 Teyon. All Rights Reserved.


#include "GameManager.h"

int UGameManager::GetLaps() const
{
	return Laps;
}

void UGameManager::SetLaps(const int NewLaps)
{
	Laps = NewLaps;
}
