#include "Discovery/DiscoveryItem.h"
#include "Discovery/DiscoveryItemData.h"
#include "Discovery/DiscoveryLogSubsystem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"

ADiscoveryItem::ADiscoveryItem()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->InitSphereRadius(150.f);
	InteractionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ADiscoveryItem::OnInteract_Implementation(APawn* Interactor)
{
	if (!ItemData)
	{
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UDiscoveryLogSubsystem* Log = GI ? GI->GetSubsystem<UDiscoveryLogSubsystem>() : nullptr;
	if (!Log || !Log->AddDiscovery(ItemData))
	{
		return;
	}

	if (PickupEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PickupEffect, GetActorLocation());
	}

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

FText ADiscoveryItem::GetInteractionPrompt_Implementation() const
{
	return ItemData ? ItemData->DisplayName : FText::FromString(TEXT("Discovery"));
}
