// Fill out your copyright notice in the Description page of Project Settings.

#include "Etos.h"
#include "EtosPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Etos/FunctionLibraries/UtilityFunctionLibrary.h"
#include "Etos/UI/InGameUI.h"
#include "Etos/Game/EtosHUD.h"

//ABuilding * AEtosPlayerController::GetBuildingUnderCursor()
//{
//
//	UKismetSystemLibrary::LineTraceSingleForObjects(this, )
//	return nullptr;
//}

void AEtosPlayerController::BeginPlay()
{
	SetupInputComponent();
	AddHUDToViewport();
	InitResourceMapping();
}

FORCEINLINE void AEtosPlayerController::SetupInputComponent()
{
	InputComponent->BindAction("Build", IE_Pressed, this, &AEtosPlayerController::BuildNewBuilding);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AEtosPlayerController::PauseGame);
	InputComponent->BindAction("Escape", IE_Pressed, this, &AEtosPlayerController::ShowGameMenu);
	InputComponent->BindAction("ClickRepeatedly", IE_Pressed, this, &AEtosPlayerController::ClickRepeatedly);
	InputComponent->BindAction("CancelBuilding", IE_Pressed, this, &AEtosPlayerController::CancelBuilding);
}

FORCEINLINE void AEtosPlayerController::AddResource(FResource resource)
{
	if (resource.Type != EResource::None)
	{
		resourceAmounts[resource.Type] += resource.Amount;
		GetInGameUI()->UpdateResourceAmounts();
	}
}

FORCEINLINE void AEtosPlayerController::RemoveResource(FResource resource)
{
	if (resource.Type != EResource::None)
	{
		resourceAmounts[resource.Type] -= resource.Amount;
		GetInGameUI()->UpdateResourceAmounts();
	}
}

FORCEINLINE int32 AEtosPlayerController::GetResourceAmount(EResource resource)
{
	return resourceAmounts[resource];
}

FORCEINLINE UInGameUI * AEtosPlayerController::GetInGameUI()
{
	return UUtilityFunctionLibrary::GetEtosHUD(this)->GetInGameUI();
}

FORCEINLINE void AEtosPlayerController::PauseGame(FKey key)
{
}

FORCEINLINE void AEtosPlayerController::BuildNewBuilding(FKey key)
{
	if (newBuilding && newBuilding->Data.bIsHeld)
	{
		if (!newBuilding->Data.bPositionIsBlocked)
		{
			if (HasEnoughResources(newBuilding->Data.BuildCost))
			{
				newBuilding->Data.bIsHeld = false;
				bIsHoldingObject = false;
				PayCostsOfBuilding(newBuilding->Data.BuildCost);

				//TODO: make building opaque

				newBuilding->OnBuild();
			}
		}
	}
}

FORCEINLINE void AEtosPlayerController::ShowGameMenu(FKey key)
{
}

FORCEINLINE void AEtosPlayerController::ClickRepeatedly(FKey key)
{
	if (bIsHoldingObject)
	{
		BuildNewBuilding(key);
		SpawnBuilding(newBuilding, newBuilding->Data);
	}
}

FORCEINLINE bool AEtosPlayerController::HasEnoughResources(TArray<FResource> buildCost)
{
	for (FResource cost : buildCost)
	{
		if (cost.Amount > resourceAmounts[cost.Type])
		{
			return false;
		}
	}
	return true;
}

FORCEINLINE void AEtosPlayerController::AddHUDToViewport()
{
	GetInGameUI()->AddToViewport();
}

FORCEINLINE void AEtosPlayerController::InitResourceMapping()
{
}

FORCEINLINE void AEtosPlayerController::CancelPlacementOfBuilding()
{
	if (bIsHoldingObject)
	{
		if (newBuilding)
		{
			newBuilding->Destroy();
			bIsHoldingObject = false;
		}
	}
}

FORCEINLINE void AEtosPlayerController::PayCostsOfBuilding(TArray<FResource> buildCost)
{
	for (FResource resource : buildCost)
	{
		RemoveResource(resource);
	}
}

FORCEINLINE void AEtosPlayerController::CancelBuilding(FKey key)
{
	CancelPlacementOfBuilding();
}

FORCEINLINE ABuilding* AEtosPlayerController::SpawnBuilding(ABuilding* Class, FBuildingData Data)
{
	if (bIsHoldingObject)
		return nullptr;

	if (!Class)
		return nullptr;

	FBuildingData data = Data;

	if (UWorld* World = GetWorld())
	{
		newBuilding = World->SpawnActor<ABuilding>(Class->GetClass());
		newBuilding->Data = data;
		newBuilding->Data.bIsHeld = true;
		bIsHoldingObject = true;

		//TODO: make building transparent
		return newBuilding;
	}
	return nullptr;
}
