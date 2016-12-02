// © 2016 - 2017 Daniel Bortfeld

#pragma once

#include "GameFramework/Actor.h"
#include "ObjectPool.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResetObjectDelegate, AActor*, ResetObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNullObjectDelegate, int32, amountOfNulledObjects);

USTRUCT()
struct FObjectPool
{
	GENERATED_BODY()

public:

	// Use to reset the returned object
	UPROPERTY()
		FResetObjectDelegate OnGetValidObject;

	UPROPERTY()
		FNullObjectDelegate OnRemovedNullptrs;

private:

	UPROPERTY(VisibleAnywhere, Category = "Object Pool")
		int32 minPooledObjects = 1;
	UPROPERTY(VisibleAnywhere, Category = "Object Pool")
		int32 maxPooledObjects = 10;

	UPROPERTY(VisibleAnywhere, Category = "Object Pool")
		TArray<UObject*> pooledObjects;

public:

	// Sets default values for this actor's properties
	FObjectPool();

	bool AddObjectToPool(UObject* Object);

	UObject* GetPooledObject(bool& bIsValid);

	template<class T>
	T* GetPooledObject(bool& bIsValid);

	int32 GetMinPooledObjectsAmount();

	void SetMinPooledObjectsAmount(int32 minPooledObjects);

	int32 GetMaxPooledObjectsAmount();

	void SetMaxPooledObjectsAmount(int32 maxPooledObjects);
};

template<class T>
inline T * FObjectPool::GetPooledObject(bool& bIsValid)
{
	bIsValid = false;

	const int32 pooledObjectsNum = pooledObjects.Num();
	if (pooledObjectsNum > 0)
	{
		bool allowShrinking = pooledObjectsNum - 1 > minPooledObjects;
		T* pooledObject = dynamic_cast<T*, UObject>(pooledObjects.Pop(allowShrinking));

		if (pooledObject && pooledObject->IsValidLowLevel())
		{
			bIsValid = true;
			if (OnGetValidObject.IsBound())
			{
				OnGetValidObject.Broadcast(pooledObject);
			}
		}
		else
		{
			for (auto obj : pooledObjects)
			{
				if (obj == nullptr)
				{

				}
			}

			pooledObjects.Shrink();
			return GetPooledObject<T>(bIsValid);
		}

		return pooledObject;
	}

	return nullptr;
}