#include "Discovery/DiscoveryLogSubsystem.h"
#include "Discovery/DiscoveryItemData.h"

bool UDiscoveryLogSubsystem::AddDiscovery(UDiscoveryItemData* Item)
{
	if (!Item || IsDiscovered(Item))
	{
		return false;
	}

	DiscoveredItems.Add(Item);
	OnDiscoveryAdded.Broadcast(Item);
	return true;
}

bool UDiscoveryLogSubsystem::IsDiscovered(const UDiscoveryItemData* Item) const
{
	return DiscoveredItems.Contains(Item);
}
