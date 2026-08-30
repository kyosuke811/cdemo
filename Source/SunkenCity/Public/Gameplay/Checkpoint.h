#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class UBoxComponent;

/** Overlap trigger that saves the current respawn point in the GameMode. */
UCLASS()
class SUNKENCITY_API ACheckpoint : public AActor
{
	GENERATED_BODY()

public:
	ACheckpoint();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerVolume;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
