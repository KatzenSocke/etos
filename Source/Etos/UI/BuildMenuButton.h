// © 2016 - 2017 Daniel Bortfeld

#pragma once

#include "Blueprint/UserWidget.h"
#include "BuildMenuButton.generated.h"

/**
 *
 */
UCLASS()
class ETOS_API UBuildMenuButton : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
		UButton* BuildButton;

	UPROPERTY()
		UImage* BuildingIcon;

	UPROPERTY()
		class ABuilding* Building;

	UPROPERTY()
		struct FBuildingData Data;

public:

	virtual void NativeConstruct() override;

private:

	UFUNCTION()
		void SpawnBuilding();

};
