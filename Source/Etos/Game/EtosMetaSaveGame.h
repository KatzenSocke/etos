// © 2016 - 2017 Daniel Bortfeld

#pragma once

#include "DateTime.h"
#include "GameFramework/SaveGame.h"
#include "EtosMetaSaveGame.generated.h"

/**
 *
 */
UCLASS()
class ETOS_API UEtosMetaSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;


	UPROPERTY()
		TMap<FString, FDateTime> SaveSlots;
};
