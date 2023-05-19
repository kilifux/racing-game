// Copyright 2023 Teyon. All Rights Reserved.


#include "ModifyMenuGameModeBase.h"
#include "CarModel.h"
#include "Kismet/GameplayStatics.h"

void AModifyMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CarModel = Cast<ACarModel>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (CarModel)
	{
	
	}
}
