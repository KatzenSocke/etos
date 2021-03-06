// © 2016 - 2017 Daniel Bortfeld

#include "Etos.h"
#include "TownCenter.h"
#include "Etos/Game/EtosPlayerController.h"
#include "Etos/Game/EtosGameMode.h"

void ATownCenter::BeginPlay()
{
	Super::BeginPlay();

	if (AEtosGameMode* const GM = Util::GetEtosGameMode(this))
	{
		peasantNeeds = GM->GetPeasantNeeds();
	}
}

void ATownCenter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Data.bIsBuilt)
	{
		ConsumeResources(DeltaTime);
		//PayTaxes(DeltaTime);
	}
}

void ATownCenter::PayTaxes(float DeltaTime)
{
	taxesTimerPassed += DeltaTime;
	if (taxesTimerPassed >= taxesTimerTotal)
	{
		taxesTimerPassed = 0;

		payedTaxes += registeredResidents * taxPerResident * (taxesTimerTotal / 60);

		int32 taxes = payedTaxes;
		payedTaxes -= taxes;

		if (MyPlayerController)
		{
			MyPlayerController->AddResource(FResource(EResource::Money, taxes));
		}
		else
		{
			GetMyPlayerController();
		}
	}
}

void ATownCenter::ConsumeResources(float DeltaTime)
{
	for (auto con : peasantNeeds.ResourceConsumptions)
	{
		float consumptionPerFrame = con.ConsumptionPerMinute / 60.f * DeltaTime;
		consumedResources.FindOrAdd(con.Resource) += (float)registeredResidents / (float)con.Residents * consumptionPerFrame;

		int32 amount = consumedResources[con.Resource];
		consumedResources[con.Resource] -= amount;

		if (MyPlayerController)
		{
			MyPlayerController->TryRemovingResource(con.Resource, amount);
		}
	}
}

void ATownCenter::UpdatePopulation(EResidentLevel level, int32 delta)
{
	registeredResidents += delta;
	if (MyPlayerController)
	{
		MyPlayerController->UpdatePopulation(level, delta);
	}
	else
	{
		GetMyPlayerController();
	}
}

void ATownCenter::UpdatePopulation(EResidentLevel from, EResidentLevel to, int32 residents)
{
	if (MyPlayerController)
	{
		MyPlayerController->UpdatePopulation(from, to, residents);
	}
	else
	{
		GetMyPlayerController();
	}
}

bool ATownCenter::HasResource(EResource in resource)
{
	return MyPlayerController->GetResourceAmount(resource) > 0;
}

void ATownCenter::BindDelayAction()
{
	if (Action.IsBound())
	{
		Action.Unbind();
	}
}
