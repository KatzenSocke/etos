// © 2016 - 2017 Daniel Bortfeld

#pragma once

#include "Etos/Buildings/Base/Building.h"
#include "Blueprint/UserWidget.h"
#include "ResourceLayout.generated.h"

/**
 *
 */
UCLASS()
class ETOS_API UResourceLayout : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "LayoutData")
		FResource Resource;

	UPROPERTY(BlueprintReadWrite, Category = "LayoutData")
		int32 MaxStoredResources;

public:

	UFUNCTION(BlueprintPure, Category = "LayoutData")
		float GetStoredPercentage() { return (float)Resource.Amount / MaxStoredResources; }
};

