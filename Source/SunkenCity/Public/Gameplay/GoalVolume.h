#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalVolume.generated.h"

class UBoxComponent;

/** Placed at the final viewpoint. Overlapping it ends the vertical slice. */
UCLASS()
class SUNKENCITY_API AGoalVolume : public AActor
{
	GENERATED_BODY()

public:
	AGoalVolume();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerVolume;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
