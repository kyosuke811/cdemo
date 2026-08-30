#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/** Implemented by anything the player can interact with: discoveries, levers, gates. */
class SUNKENCITY_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void OnInteract(APawn* Interactor);

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	FText GetInteractionPrompt() const;
};
