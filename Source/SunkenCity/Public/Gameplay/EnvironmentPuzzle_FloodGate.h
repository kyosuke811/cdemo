#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/IInteractable.h"
#include "EnvironmentPuzzle_FloodGate.generated.h"

class UStaticMeshComponent;

/**
 * The prototype's one environmental gimmick: interact with the drainage
 * lever to raise blocking gates out of the way and lower nearby water
 * bodies, opening a route that was previously flooded/blocked.
 * Assign GatesToOpen / WaterBodiesToLower in the editor (or via Python).
 */
UCLASS()
class SUNKENCITY_API AEnvironmentPuzzle_FloodGate : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AEnvironmentPuzzle_FloodGate();

	virtual void OnInteract_Implementation(APawn* Interactor) override;
	virtual FText GetInteractionPrompt_Implementation() const override;

	UPROPERTY(EditAnywhere, Category = "Puzzle")
	TArray<TObjectPtr<AActor>> GatesToOpen;

	UPROPERTY(EditAnywhere, Category = "Puzzle")
	TArray<TObjectPtr<AActor>> WaterBodiesToLower;

	UPROPERTY(EditAnywhere, Category = "Puzzle")
	float GateOpenHeight = 400.f;

	UPROPERTY(EditAnywhere, Category = "Puzzle")
	float WaterLowerAmount = 300.f;

	UPROPERTY(EditAnywhere, Category = "Puzzle")
	float ActivationDuration = 3.f;

protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LeverMesh;

private:
	bool bIsActivated = false;
	bool bIsAnimating = false;
	float AnimTimer = 0.f;
	TMap<TObjectPtr<AActor>, FVector> GateStartLocations;
	TMap<TObjectPtr<AActor>, FVector> WaterStartLocations;
};
