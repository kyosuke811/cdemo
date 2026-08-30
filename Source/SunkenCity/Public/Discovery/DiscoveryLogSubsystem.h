#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DiscoveryLogSubsystem.generated.h"

class UDiscoveryItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDiscoveryAdded, UDiscoveryItemData*, Item);

/** Tracks which discoveries the player has found this session. Bind to OnDiscoveryAdded from UI. */
UCLASS()
class SUNKENCITY_API UDiscoveryLogSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Discovery")
	bool AddDiscovery(UDiscoveryItemData* Item);

	UFUNCTION(BlueprintPure, Category = "Discovery")
	bool IsDiscovered(const UDiscoveryItemData* Item) const;

	UFUNCTION(BlueprintPure, Category = "Discovery")
	int32 GetDiscoveryCount() const { return DiscoveredItems.Num(); }

	UFUNCTION(BlueprintPure, Category = "Discovery")
	const TArray<UDiscoveryItemData*>& GetDiscoveredItems() const { return DiscoveredItems; }

	UPROPERTY(BlueprintAssignable, Category = "Discovery")
	FOnDiscoveryAdded OnDiscoveryAdded;

private:
	UPROPERTY()
	TArray<TObjectPtr<UDiscoveryItemData>> DiscoveredItems;
};
