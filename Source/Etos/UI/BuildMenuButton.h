// © 2016 - 2017 Daniel Bortfeld

#pragma once

#include "UMG.h"
#include "UMGStyle.h"
#include "Slate/SObjectWidget.h"
#include "IUMGModule.h"
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

	UPROPERTY(BlueprintReadOnly, Category = "UIElements")
		UButton* BuildButton;

	UPROPERTY(BlueprintReadOnly, Category = "UIElements")
		UImage* BuildingIcon;

	UPROPERTY()
		TSubclassOf<ABuilding> Building;

	UPROPERTY()
		struct FBuildingData Data;

	UPROPERTY(BlueprintReadOnly, Category = "UIElements")
		UTexture2D* IconusRectus;

public:

	//virtual bool Initialize() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Initialization", meta = (DisplayName = "OnInitialization"))
		void BPEvent_OnInitialization();

	// Create a reference between the elements in the designer and the elements in C++
	//UFUNCTION(BlueprintCallable, Category = "UIElements")
	//	void SetButtonAndIcon(UPARAM(DisplayName = "Bulid Button") UButton* button, UPARAM(DisplayName = "Building Icon")  UImage* icon);

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void BindBuildButton(UPARAM(DisplayName = "Bulid Button") UButton* button);

private:

	UFUNCTION()
		void SpawnBuilding();
};
