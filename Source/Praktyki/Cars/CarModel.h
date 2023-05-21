// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CarModel.generated.h"

UCLASS()
class PRAKTYKI_API ACarModel : public APawn
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* SteeringWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* RearSpoiler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* SeatNetClamps;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* WingMirrorLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* WingMirrorRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* CockpitConsole;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* Net;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* ExteriorInteriorWindows;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* EngineComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* WheelRightFront;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* WheelRightRear;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* WheelLeftFront;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* WheelLeftRear;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* RearDiffuser;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* FenderLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* DoorLeft;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* DoorRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* FenderRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* RearBumper;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* FrontBumper;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* FrontHood;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* Interior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* MainBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* RearBoot;

public:
	// Sets default values for this pawn's properties
	ACarModel();
	
	//Setters for changing car Material in Modify Menu
	void SetMaterialFrontHood(const float Index);
	void SetMaterialMainBody(const float Index);
	void SetMaterialFrontBumper(const float Index);
	void SetMaterialRearBumper(const float Index);
	void SetMaterialRearBoot(const float Index);
	void SetMaterialOthers(const float Index);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Car materials use in Modify Menu
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Materials, meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInterface*> Materials;

	class UGameInstanceBase* GameInstanceBase;
};
