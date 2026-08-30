#include "Gameplay/Checkpoint.h"
#include "Components/BoxComponent.h"
#include "SunkenCityGameMode.h"
#include "GameFramework/Pawn.h"

ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->SetBoxExtent(FVector(150.f, 150.f, 200.f));
	TriggerVolume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->IsA<APawn>())
	{
		return;
	}

	if (ASunkenCityGameMode* GM = GetWorld()->GetAuthGameMode<ASunkenCityGameMode>())
	{
		GM->SetCheckpoint(GetActorTransform());
	}
}
