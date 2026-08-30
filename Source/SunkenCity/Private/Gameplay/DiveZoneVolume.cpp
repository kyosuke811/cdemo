#include "Gameplay/DiveZoneVolume.h"
#include "Components/BoxComponent.h"
#include "SunkenCityCharacter.h"

ADiveZoneVolume::ADiveZoneVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	RootComponent = Volume;
	Volume->SetBoxExtent(FVector(500.f, 500.f, 300.f));
	Volume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ADiveZoneVolume::BeginPlay()
{
	Super::BeginPlay();
	Volume->OnComponentBeginOverlap.AddDynamic(this, &ADiveZoneVolume::OnBeginOverlap);
	Volume->OnComponentEndOverlap.AddDynamic(this, &ADiveZoneVolume::OnEndOverlap);
}

void ADiveZoneVolume::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASunkenCityCharacter* PlayerCharacter = Cast<ASunkenCityCharacter>(OtherActor))
	{
		PlayerCharacter->SetSubmerged(true);
	}
}

void ADiveZoneVolume::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (ASunkenCityCharacter* PlayerCharacter = Cast<ASunkenCityCharacter>(OtherActor))
	{
		PlayerCharacter->SetSubmerged(false);
	}
}
