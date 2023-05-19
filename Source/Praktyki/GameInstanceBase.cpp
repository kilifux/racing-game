// Copyright 2023 Teyon. All Rights Reserved.


#include "GameInstanceBase.h"

int UGameInstanceBase::GetFrontHoodIndex() const
{
	return FrontHoodIndex;
}

void UGameInstanceBase::SetFrontHoodIndex(const int NewFrontHoodIndex)
{
	FrontHoodIndex = NewFrontHoodIndex;
}

int UGameInstanceBase::GetMainBodyIndex() const
{
	return MainBodyIndex;
}

void UGameInstanceBase::SetMainBodyIndex(const int NewMainBodyIndex)
{
	MainBodyIndex = NewMainBodyIndex;
}

int UGameInstanceBase::GetFrontBumperIndex() const
{
	return FrontBumperIndex;
}

void UGameInstanceBase::SetFrontBumperIndex(const int NewFrontBumperIndex)
{
	FrontBumperIndex = NewFrontBumperIndex;
}

int UGameInstanceBase::GetRearBumperIndex() const
{
	return RearBumperIndex;
}

void UGameInstanceBase::SetRearBumperIndex(const int NewRearBumperIndex)
{
	RearBumperIndex = NewRearBumperIndex;
}

int UGameInstanceBase::GetRearBootIndex() const
{
	return RearBootIndex;
}

void UGameInstanceBase::SetRearBootIndex(const int NewRearBootIndex)
{
	RearBootIndex = NewRearBootIndex;
}

int UGameInstanceBase::GetOthersIndex() const
{
	return OthersIndex;
}

void UGameInstanceBase::SetOthersIndex(const int NewOthersIndex)
{
	OthersIndex = NewOthersIndex;
}

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
