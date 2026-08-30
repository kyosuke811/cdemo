#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DiscoveryItemData.generated.h"

class UTexture2D;

/** Static definition of one discoverable object (photo, sign, note...). Create instances as Data Assets in the editor. */
UCLASS(BlueprintType)
class SUNKENCITY_API UDiscoveryItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Discovery")
	FName DiscoveryId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Discovery")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Discovery", meta = (MultiLine = true))
	FText ShortDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Discovery")
	TSoftObjectPtr<UTexture2D> Icon;
};
