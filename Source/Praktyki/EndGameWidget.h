// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* TXTTableResults;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UBorder* TableBorderResults;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* RestartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* ExitButton;

	int Minutes;
	int Seconds;
	int Milliseconds;
	
public:
	UEndGameWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetTableResults(int Index, float BestLapTime, float FinalTime);
	FString TimeToFormat(float TimeToFormat);

	UFUNCTION()
	void RestartLevel();
};
