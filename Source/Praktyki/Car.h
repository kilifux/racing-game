// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PRAKTYKI_API ACar : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	
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
	
	bool Choose = true;

	FVector ThrottleAxisVector;
	APlayerController* PlayerController;
	float MaxSpeed;
	FVector CurrentVelocity;

public:
	UFUNCTION(BlueprintCallable)
	int GetCurrentSpeed() const;
	
	void SetCurrentSpeed();

private:
	float SteeringSensitivity;
	float Acceleration;
	float MaxAngularSpeed;
	float SkidThreshold;

	int CurrentLap;
	int CurrentSpeed;

	TArray<float> LapTimes;
	float LapTime = 0;
	float CurrentTime = 0;
	float LastTime = 0;
	float BestTime = 0;
	float FinalTime = 0;

public:
	float GetFinalTime() const;

	UFUNCTION(BlueprintCallable)
	float GetBestTime() const;

	UFUNCTION(BlueprintCallable)
	TArray<float> GetLapTimes() const;

	UFUNCTION(BlueprintCallable)
	float GetLastTime() const;

private:
	FTimerHandle CurrentVelocityTimerHandle;

public:
	// Sets default values for this pawn's properties
	ACar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookAround(const FInputActionValue& Value);

	void Steering(const FInputActionValue& Value);

	void Throttle(const FInputActionValue& Value);

	void ToggleCamera();

	UFUNCTION(BlueprintCallable)
	int GetCurrentLap() const;
	
	void AddLap();

};
