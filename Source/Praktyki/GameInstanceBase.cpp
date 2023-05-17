// Copyright 2023 Teyon. All Rights Reserved.


#include "GameInstanceBase.h"

int UGameInstanceBase::GetLaps() const
{
	return Laps;
}

void UGameInstanceBase::SetLaps(const int NewLaps)
{
	Laps = NewLaps;
}

int UGameInstanceBase::GetMode() const
{
	return Mode;
}

void UGameInstanceBase::SetMode(const int NewMode)
{
	Mode = NewMode;
}

float UGameInstanceBase::GetMaxTime() const
{
	return MaxTime;
}

void UGameInstanceBase::SetMaxTime(const float NewMaxTime)
{
	MaxTime = NewMaxTime;
}
