// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CarModel.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "Car.generated.h"

UCLASS()
class PRAKTYKI_API ACar : public ACarModel
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();
	
	//Get the total sum of lap times
	float GetFinalTime() const { return FinalTime; }
	
	//Get the time of the fastest lap
	float GetBestTime() const { return BestTime; }
	
	TArray<float> GetLapTimes() const { return LapTimes; }

	TArray<float> GetDeltaTimes() const {return DeltaTimes; }
	
	//Get the current lap number
	int GetCurrentLap() const { return CurrentLap; }
	
	//Add one to the lap counter and update the lap times
	virtual void AddLap();

	//Uses to get Best Time 
	static float Min(TArray<float> Array);
	
protected:
	
	class ACarPlayerController* PlayerController;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> MaterialInterfaceLights;
	
	float SteeringSensitivity;
	float Acceleration;
	float MaxAngularSpeed;
	float SkidThreshold;
	float MaxSpeed;
	
	int CurrentLap;
	
	FVector ThrottleAxisVector;
	FVector SteeringAxisVector; 
	FVector CurrentVelocity;
	
	TArray<float> LapTimes;
	TArray<float> DeltaTimes;
	
	float LapTime = 0;
	float CurrentTime = 0;
	float LastTime = 0;
	float BestTime = 0;
	float FinalTime = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Throttle(const FInputActionValue& Value);
	
	void Steering(const FInputActionValue& Value);
	
	//Exit to Main Menu by clicking ESC
	void Exit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
