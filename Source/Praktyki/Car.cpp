// Copyright 2023 Teyon. All Rights Reserved.

#include "Car.h"
#include "CarPlayerController.h"
#include "InputActionValue.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MaxSpeed = 2350;
	Acceleration = 1700000;
	SteeringSensitivity = 5000;
	MaxAngularSpeed = 50;
	SkidThreshold = 0.3f;
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<ACarPlayerController>(Controller);
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentTime = PlayerController->GetGameTimeSinceCreation();
	LastTime = PlayerController->GetGameTimeSinceCreation() - LapTime;
}

void ACar::AddLap()
{
	CurrentLap += 1;
	if (PlayerController)
	{
		LapTime = PlayerController->GetGameTimeSinceCreation();;
	}
	
	LapTimes.Add(LastTime);
	DeltaTimes.Add(BestTime - LastTime);
	BestTime = Min(LapTimes);
}

float ACar::Min(TArray<float> Array)
{
	check(Array.Num() > 0);

	float MinValue = Array[0];
	for (int i = 1; i < Array.Num(); ++i)
	{
		if (Array[i] < MinValue)
		{
			MinValue = Array[i];
		}
	}
	
	return MinValue;
}

void ACar::Throttle(const FInputActionValue& Value)
{
	ThrottleAxisVector = Value.Get<FVector>();

	if (ThrottleAxisVector.X <= 0)
	{
		ThrottleAxisVector.X /= 1.5;
		RearBumper->SetMaterial(3, MaterialInterfaceLights[1]);
	}
	else
	{
		RearBumper->SetMaterial(3, MaterialInterfaceLights[0]);
	}
	
	SkeletalMeshComponent->AddForce(GetActorForwardVector() * ThrottleAxisVector.X * Acceleration);
	CurrentVelocity = SkeletalMeshComponent->GetPhysicsLinearVelocity();
	
	if (CurrentVelocity.Length() > MaxSpeed)
	{
		SkeletalMeshComponent->SetPhysicsLinearVelocity(CurrentVelocity.GetSafeNormal() * MaxSpeed);
	}
}

void ACar::Steering(const FInputActionValue& Value)
{
	SteeringAxisVector = Value.Get<FVector>();
	
	// Calculate the steering angle based on the input value and SteeringSensitivity
	float SteeringAngle = SteeringAxisVector.X * SteeringSensitivity;

	// Calculate the value of the turning force
	float SteeringForce = SteeringAngle * SteeringSensitivity;

	// Check the direction of vehicle movement and invert the sign of the turning force if it is moving in reverse
	FVector Velocity = SkeletalMeshComponent->GetPhysicsLinearVelocity();
	float Speed = Velocity.Size();
	FVector ForwardVector = GetActorForwardVector();
	float DotProduct = FVector::DotProduct(Velocity.GetSafeNormal(), ForwardVector);
	if (DotProduct < 0)
	{
		SteeringForce *= -1;
	}

	
	float NormalizedSpeed = Speed / MaxSpeed;
	float SteeringForceLimited = SteeringForce * NormalizedSpeed;
	FVector TorqueVector = FVector(0.0f, 0.0f, SteeringForceLimited);
	
	SkeletalMeshComponent->AddTorqueInRadians(TorqueVector);
}




