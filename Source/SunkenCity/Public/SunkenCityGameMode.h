#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SunkenCityGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPrototypeComplete);

UCLASS()
class SUNKENCITY_API ASunkenCityGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASunkenCityGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void SetCheckpoint(const FTransform& NewCheckpoint);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void RespawnAtCheckpoint(AActor* PlayerActor);

	UFUNCTION(BlueprintCallable, Category = "Goal")
	void CompletePrototype();

	UFUNCTION(BlueprintPure, Category = "Goal")
	bool IsPrototypeComplete() const { return bIsComplete; }

	UPROPERTY(BlueprintAssignable, Category = "Goal")
	FOnPrototypeComplete OnPrototypeComplete;

private:
	FTransform CurrentCheckpoint;
	bool bIsComplete = false;
};
