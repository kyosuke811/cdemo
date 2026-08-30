#include "Gameplay/EnvironmentPuzzle_FloodGate.h"
#include "Components/StaticMeshComponent.h"

AEnvironmentPuzzle_FloodGate::AEnvironmentPuzzle_FloodGate()
{
	PrimaryActorTick.bCanEverTick = true;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));
	RootComponent = LeverMesh;
	LeverMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
}

void AEnvironmentPuzzle_FloodGate::OnInteract_Implementation(APawn* Interactor)
{
	if (bIsActivated)
	{
		return;
	}

	bIsActivated = true;
	bIsAnimating = true;
	AnimTimer = 0.f;

	GateStartLocations.Empty();
	for (AActor* Gate : GatesToOpen)
	{
		if (Gate)
		{
			GateStartLocations.Add(Gate, Gate->GetActorLocation());
		}
	}

	WaterStartLocations.Empty();
	for (AActor* Water : WaterBodiesToLower)
	{
		if (Water)
		{
			WaterStartLocations.Add(Water, Water->GetActorLocation());
		}
	}
}

FText AEnvironmentPuzzle_FloodGate::GetInteractionPrompt_Implementation() const
{
	return bIsActivated
		? FText::FromString(TEXT("Drainage mechanism already activated"))
		: FText::FromString(TEXT("Activate the old drainage mechanism"));
}

void AEnvironmentPuzzle_FloodGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsAnimating)
	{
		return;
	}

	AnimTimer += DeltaTime;
	const float Alpha = FMath::Clamp(AnimTimer / ActivationDuration, 0.f, 1.f);

	for (const TPair<TObjectPtr<AActor>, FVector>& Pair : GateStartLocations)
	{
		if (AActor* Gate = Pair.Key)
		{
			FVector NewLocation = Pair.Value;
			NewLocation.Z += GateOpenHeight * Alpha;
			Gate->SetActorLocation(NewLocation);
		}
	}

	for (const TPair<TObjectPtr<AActor>, FVector>& Pair : WaterStartLocations)
	{
		if (AActor* Water = Pair.Key)
		{
			FVector NewLocation = Pair.Value;
			NewLocation.Z -= WaterLowerAmount * Alpha;
			Water->SetActorLocation(NewLocation);
		}
	}

	if (Alpha >= 1.f)
	{
		bIsAnimating = false;
		for (const TPair<TObjectPtr<AActor>, FVector>& Pair : GateStartLocations)
		{
			if (AActor* Gate = Pair.Key)
			{
				Gate->SetActorEnableCollision(false);
			}
		}
	}
}
