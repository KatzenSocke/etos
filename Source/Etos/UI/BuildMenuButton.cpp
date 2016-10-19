// © 2016 - 2017 Daniel Bortfeld

#include "Etos.h"
#include "Etos/Buildings/Base/Building.h"
#include "Etos/FunctionLibraries/UtilityFunctionLibrary.h"
#include "Etos/Game/EtosPlayerController.h"
#include "BuildMenuButton.h"

void UBuildMenuButton::NativeConstruct()
{
	if (BuildButton)
	{
		BuildButton->OnReleased.AddDynamic(this, &UBuildMenuButton::SpawnBuilding);
	}
}

void UBuildMenuButton::SpawnBuilding()
{
	UUtilityFunctionLibrary::GetFirstEtosPlayerController(this)->SpawnBuilding(Building, Data);
}
