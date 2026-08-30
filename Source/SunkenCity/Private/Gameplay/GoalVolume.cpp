#include "Gameplay/GoalVolume.h"
#include "Components/BoxComponent.h"
#include "SunkenCityGameMode.h"
#include "GameFramework/Pawn.h"

AGoalVolume::AGoalVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->SetBoxExtent(FVector(200.f, 200.f, 300.f));
	TriggerVolume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AGoalVolume::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AGoalVolume::OnOverlapBegin);
}

void AGoalVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->IsA<APawn>())
	{
		return;
	}

	if (ASunkenCityGameMode* GM = GetWorld()->GetAuthGameMode<ASunkenCityGameMode>())
	{
		GM->CompletePrototype();
	}
}
