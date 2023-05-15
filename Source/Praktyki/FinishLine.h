// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishLine.generated.h"

UCLASS()
class PRAKTYKI_API AFinishLine : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftPole;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightPole;

	class ACar* Car;
	class APraktykiGameModeBase* PraktykiGameModeBase;

public:	
	// Sets default values for this actor's properties
	AFinishLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
