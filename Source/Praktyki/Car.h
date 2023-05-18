// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Car.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PRAKTYKI_API ACar : public APawn
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmInteriorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraInteriorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmExteriorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraExteriorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SteeringWheel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ToggleCameraAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAroundAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SteeringAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ThrottleAction;
	
	class AInGameHUD* InGameHUD;
	class UGameInstanceBase* GameInstanceBase;
	class ACarPlayerController* PlayerController;

public:
	// Sets default values for this pawn's properties
	ACar();
	
	int GetCurrentSpeed() const { return CurrentSpeed / 10; }
	
	void SetCurrentSpeed();
	
	//Get the remaining time until the end of the race
	float GetTimeLeft() const { return TimeLeft; }
	
	//Get the total sum of lap times
	float GetFinalTime() const { return FinalTime; }
	
	//Get the time of the fastest lap
	float GetBestTime() const { return BestTime; }
	
	TArray<float> GetLapTimes() const { return  LapTimes; }
	
	//Get the current lap number
	int GetCurrentLap() const { return CurrentLap; }
	
	//Add one to the lap counter and update the lap times
	void AddLap();

private:
	
	float SteeringSensitivity;
	float Acceleration;
	float MaxAngularSpeed;
	float SkidThreshold;

	int CurrentLap;
	int CurrentSpeed;
	FTimerHandle CurrentVelocityTimerHandle;
	
	FVector ThrottleAxisVector;
	FVector SteeringAxisVector; 
	FVector CurrentVelocity;

	//Choose of camera perspective
	bool Choose = true;
	float MaxSpeed;
	
	TArray<float> LapTimes;
	float LapTime = 0;
	float CurrentTime = 0;
	float LastTime = 0;
	float BestTime = 0;
	float FinalTime = 0;
	
	//The maximum race time set in the main menu
	float MaxTime = 30;	
	float TimeLeft = 30;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LookAround(const FInputActionValue& Value);

	void Steering(const FInputActionValue& Value);

	void Throttle(const FInputActionValue& Value);

	void ToggleCamera();
};
