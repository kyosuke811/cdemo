#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SunkenCityHUD.generated.h"

class UMainHUDWidget;

UCLASS()
class SUNKENCITY_API ASunkenCityHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	/** Optional: point this at a Widget Blueprint that inherits from UMainHUDWidget once one exists. */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMainHUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UMainHUDWidget> HUDWidgetInstance;
};
