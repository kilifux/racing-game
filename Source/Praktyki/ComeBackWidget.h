// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ComeBackWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API UComeBackWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UComeBackWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
};
