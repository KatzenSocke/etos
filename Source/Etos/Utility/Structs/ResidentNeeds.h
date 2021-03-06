// © 2016 - 2017 Daniel Bortfeld

#pragma once

#include "ResourceConsumption.h"
#include "ResidentNeeds.generated.h"

/**
*
*/
USTRUCT(BlueprintType)
struct FResidentNeeds : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EResidentLevel ResidentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FResourceConsumption> ResourceConsumptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<EResidentNeed> ResidentNeeds;

public:

	FResidentNeeds(EResidentLevel ResidentLevel = EResidentLevel::Peasant)
	{
		this->ResidentLevel = ResidentLevel;
	}
};
