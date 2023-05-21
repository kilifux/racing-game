// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ModifyMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API UModifyMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class USlider* FrontHoodSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class USlider* MainBodySlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class USlider* FrontBumperSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class USlider* RearBumperSlider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class USlider* RearBootSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	class USlider* OthersSlider;

	class UGameInstanceBase* GameInstanceBase;
	class ACarModel* CarModel;
	
public:
	UModifyMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	UFUNCTION()
	void GetFrontHoodSliderValue(float Value);
	
	UFUNCTION()
	void GetMainBodySliderValue(float Value);
	
	UFUNCTION()
	void GetFrontBumperSliderValue(float Value);
	
	UFUNCTION()
	void GetRearBumperSliderValue(float Value);
	
	UFUNCTION()
	void GetRearBootSliderValue(float Value);

	UFUNCTION()
	void GetOthersSliderValue(float Value);

	UFUNCTION()
	void ExitLevel();
	
};
