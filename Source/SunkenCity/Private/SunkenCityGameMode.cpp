#include "SunkenCityGameMode.h"
#include "SunkenCityCharacter.h"
#include "UI/SunkenCityHUD.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASunkenCityGameMode::ASunkenCityGameMode()
{
	DefaultPawnClass = ASunkenCityCharacter::StaticClass();
	HUDClass = ASunkenCityHUD::StaticClass();
}

void ASunkenCityGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			CurrentCheckpoint = Pawn->GetActorTransform();
		}
	}
}

void ASunkenCityGameMode::SetCheckpoint(const FTransform& NewCheckpoint)
{
	CurrentCheckpoint = NewCheckpoint;
}

void ASunkenCityGameMode::RespawnAtCheckpoint(AActor* PlayerActor)
{
	if (!PlayerActor)
	{
		return;
	}

	PlayerActor->SetActorLocationAndRotation(CurrentCheckpoint.GetLocation(), CurrentCheckpoint.GetRotation());

	if (ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerActor))
	{
		PlayerCharacter->GetCharacterMovement()->StopMovementImmediately();
	}
}

void ASunkenCityGameMode::CompletePrototype()
{
	if (bIsComplete)
	{
		return;
	}

	bIsComplete = true;
	OnPrototypeComplete.Broadcast();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Prototype Complete"));
	}
}
