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
	
	int Laps;
	int CurrentLap;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UUserWidget* HUDUserWidget;
	
public:
	UFUNCTION(BlueprintCallable)
	int GetLaps() const;
	
	void SetLaps(const int InLaps);

	UFUNCTION(BlueprintCallable)
	int GetCurrentLap() const;
	
	void SetCurrentLap(const int InCurrentLap);
	
	void AddLap();
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
