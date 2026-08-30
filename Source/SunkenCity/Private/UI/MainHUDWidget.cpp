#include "UI/MainHUDWidget.h"
#include "SunkenCityCharacter.h"
#include "SunkenCityGameMode.h"
#include "Discovery/DiscoveryLogSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ASunkenCityCharacter* PlayerCharacter = Cast<ASunkenCityCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		PlayerCharacter->OnOxygenChanged.AddDynamic(this, &UMainHUDWidget::HandleOxygenChanged);
		UpdateOxygen(PlayerCharacter->GetOxygenPercent());
	}

	if (UGameInstance* GI = GetGameInstance())
	{
		if (UDiscoveryLogSubsystem* Log = GI->GetSubsystem<UDiscoveryLogSubsystem>())
		{
			Log->OnDiscoveryAdded.AddDynamic(this, &UMainHUDWidget::HandleDiscoveryAdded);
		}
	}

	if (ASunkenCityGameMode* GM = Cast<ASunkenCityGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GM->OnPrototypeComplete.AddDynamic(this, &UMainHUDWidget::HandlePrototypeComplete);
	}

	GetWorld()->GetTimerManager().SetTimer(PromptPollTimer, this, &UMainHUDWidget::PollInteractionPrompt, 0.1f, true);
}

void UMainHUDWidget::HandleDiscoveryAdded(UDiscoveryItemData* Item)
{
	ShowDiscoveryToast(Item);
}

void UMainHUDWidget::HandlePrototypeComplete()
{
	ShowPrototypeComplete();
}

void UMainHUDWidget::HandleOxygenChanged(float OxygenPercent)
{
	UpdateOxygen(OxygenPercent);
}

void UMainHUDWidget::PollInteractionPrompt()
{
	if (ASunkenCityCharacter* PlayerCharacter = Cast<ASunkenCityCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		const FText Prompt = PlayerCharacter->GetCurrentInteractionPrompt();
		ShowInteractionPrompt(Prompt, !Prompt.IsEmpty());
	}
}
