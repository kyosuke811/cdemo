#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/IInteractable.h"
#include "DiscoveryItem.generated.h"

class UDiscoveryItemData;
class UStaticMeshComponent;
class USphereComponent;
class UNiagaraSystem;

/** A placeable actor representing one discoverable object in the level. Assign a placeholder mesh + a DiscoveryItemData asset. */
UCLASS()
class SUNKENCITY_API ADiscoveryItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ADiscoveryItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Discovery")
	TObjectPtr<UDiscoveryItemData> ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Discovery")
	TObjectPtr<UNiagaraSystem> PickupEffect;

	virtual void OnInteract_Implementation(APawn* Interactor) override;
	virtual FText GetInteractionPrompt_Implementation() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> InteractionSphere;
};
