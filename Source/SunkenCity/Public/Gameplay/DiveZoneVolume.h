#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiveZoneVolume.generated.h"

class UBoxComponent;

/**
 * Marks the fully-submerged portion of a water body (below the surface).
 * While the player overlaps this, they are "diving" and their oxygen drains.
 * Place this nested inside (and smaller than) an AWaterVolumePrototype.
 */
UCLASS()
class SUNKENCITY_API ADiveZoneVolume : public AActor
{
	GENERATED_BODY()

public:
	ADiveZoneVolume();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> Volume;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
