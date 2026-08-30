#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "MainHUDWidget.generated.h"

class UDiscoveryItemData;

/**
 * C++ base for the prototype's HUD widget. Create a Widget Blueprint that
 * inherits from this class in the editor and implement the events below
 * to show an oxygen bar, an interaction prompt, a discovery toast and the
 * "Prototype Complete" screen - the wiring to gameplay is already done here.
 */
UCLASS()
class SUNKENCITY_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void UpdateOxygen(float OxygenPercent);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowDiscoveryToast(UDiscoveryItemData* Item);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowInteractionPrompt(const FText& PromptText, bool bVisible);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowPrototypeComplete();

private:
	UFUNCTION()
	void HandleDiscoveryAdded(UDiscoveryItemData* Item);

	UFUNCTION()
	void HandlePrototypeComplete();

	UFUNCTION()
	void HandleOxygenChanged(float OxygenPercent);

	FTimerHandle PromptPollTimer;
	void PollInteractionPrompt();
};
