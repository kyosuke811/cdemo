#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PhysicsVolume.h"
#include "WaterVolumePrototype.generated.h"

/**
 * Placeholder swim volume. Placing one of these (sized to fill a flooded
 * street/room, top at the water surface) is enough for UE's stock
 * CharacterMovementComponent to switch the player into MOVE_Swimming.
 * In Phase 6 this can be replaced/paired with a real Water plugin body for visuals.
 */
UCLASS()
class SUNKENCITY_API AWaterVolumePrototype : public APhysicsVolume
{
	GENERATED_BODY()

public:
	AWaterVolumePrototype();
};
