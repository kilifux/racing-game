// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"


UCLASS()
class PRAKTYKI_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* RaceSettingsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* TrackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* ModifyCarButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* ExitGameButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class USlider* LapSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* LapSliderText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class USlider* MaxTimeSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* MaxTimeText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class USlider* ModeSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* ModeText;
	
	int Minutes;
	int Seconds;
	
	class UGameInstanceBase* GameInstanceBase;

public:
	
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	FString TimeToFormat(float TimeToFormat);

	UFUNCTION()
	void GetLapSliderValue(float Value);

	UFUNCTION()
	void GetMaxTimeValue(float Value);

	UFUNCTION()
	void GetModeValue(float Value);

	UFUNCTION()
	void StartLevel();

	UFUNCTION()
	void StartModifyMenu();

	UFUNCTION()
	void ExitGame();
};
