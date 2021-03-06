// © 2016 - 2017 Daniel Bortfeld

#include "Etos.h"
#include "ResourcePopup.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "Etos/Game/EtosPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AResourcePopup::AResourcePopup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 2;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(RootComponent);
}

// Called every frame
void AResourcePopup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// go up
	AddActorWorldOffset(FVector(0, 0, UpSpeed*DeltaTime));

	if (!PlayerCameraManager)
		PlayerCameraManager = Util::GetFirstEtosPlayerController(this)->PlayerCameraManager;

	//look to camera
	if (PlayerCameraManager)
	{
		FVector cameraLocation = PlayerCameraManager->GetCameraLocation();

		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(cameraLocation + PlayerCameraManager->GetCameraRotation().Vector(), cameraLocation);

		SetActorRotation(rotation);
	}
}

