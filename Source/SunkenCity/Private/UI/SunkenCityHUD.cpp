#include "UI/SunkenCityHUD.h"
#include "UI/MainHUDWidget.h"
#include "Blueprint/UserWidget.h"

void ASunkenCityHUD::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<UMainHUDWidget> ClassToUse = HUDWidgetClass ? HUDWidgetClass : UMainHUDWidget::StaticClass();
	HUDWidgetInstance = CreateWidget<UMainHUDWidget>(GetOwningPlayerController(), ClassToUse);
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->AddToViewport();
	}
}
