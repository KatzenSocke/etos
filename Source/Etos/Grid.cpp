// © 2016 - 2017 Daniel Bortfeld

#include "Etos.h"
#include "Grid.h"


// Sets default values
AGrid::AGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GridMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Grid Mesh");
	RootComponent = GridMesh;
	GridMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2); // Floor
	GridMesh->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrid::OnConstruction(const FTransform & Transform)
{
	if (bConstruct)
	{
		GridMesh->ClearInstances();
		for (int32 i = 0; i < Width * Height; i++)
		{
			float X = i / Height * TileSize;
			float Y = i % Height * TileSize;
			GridMesh->AddInstance(FTransform(FVector(X, Y, 0)));
		}
	}
}

