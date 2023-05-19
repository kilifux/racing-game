// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Car.h"
#include "CarPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API ACarPlayer : public ACar
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmInteriorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraInteriorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmExteriorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraExteriorComponent;

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ExitAction;

	class AInGameHUD* InGameHUD;
	class UGameInstanceBase* GameInstanceBase;

public:
	ACarPlayer();

	void LookAround(const FInputActionValue& Value);

	void ToggleCamera();
	
	int GetCurrentSpeed() const { return CurrentSpeed / 10; }
	
	void SetCurrentSpeed();

	virtual void AddLap() override;

	void CheckGround();

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ComeBackWidgetClass;

	class UComeBackWidget* ComeBackWidget;
	
	//Choose of camera perspective
	bool Choose = true;
	bool bTimeExpired;

	int CurrentSpeed;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	
	FTimerHandle CurrentVelocityTimerHandle;
	FTimerHandle CheckGroundTimerHandle;

	//The maximum race time set in the main menu
	float MaxTime = 30;	
	float TimeLeft = 30;

	int OffRoadTimes;
	
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
