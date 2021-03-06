// © 2016 - 2017 Daniel Bortfeld

#include "Etos.h"
#include "SimpleCollisionManager.h"
#include "BoxCollider.h"

// Sets default values
ASimpleCollisionManager::ASimpleCollisionManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void ASimpleCollisionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckCollisions();
}

void ASimpleCollisionManager::RegisterCollider(UBoxCollider * Collider)
{
	registeredColliders.AddUnique(Collider);
}

void ASimpleCollisionManager::UnregisterCollider(UBoxCollider * Collider)
{
	if (Collider->IsValidLowLevel())
	{
		if (registeredColliders.Contains(Collider))
		{
			Collider->SetGenerateCollisionEvents(false);
			for (UBoxCollider* A : registeredColliders)
			{
				if (A && A->IsValidLowLevel())
				{
					A->CheckCollision(Collider);
				}
			}
			registeredColliders.Remove(Collider);
		}
	}
	else
	{
		registeredColliders.Remove(Collider);
		registeredColliders.Shrink();
	}
}

void ASimpleCollisionManager::CheckCollisions()
{
	bool bEverythingIsAwesome = true;

	for (UBoxCollider* A : registeredColliders)
	{
		if (A && A->IsValidLowLevel())
		{
			for (UBoxCollider* B : registeredColliders)
			{
				if (A != B)
				{
					if (B && B->IsValidLowLevel())
					{
						A->CheckCollision(B);
					}
					else bEverythingIsAwesome = false;
				}
			}
		}
		else bEverythingIsAwesome = false;
	}

	if (!bEverythingIsAwesome)
	{// remove invalid entries
		registeredColliders.Shrink();
		//for (int32 i = 0; i < registeredColliders.Num(); ++i)
		//{
		//	if (!registeredColliders[i]->IsValidLowLevel())
		//	{
		//		UnregisterCollider(registeredColliders[i]);
		//	}
		//}
	}
}

