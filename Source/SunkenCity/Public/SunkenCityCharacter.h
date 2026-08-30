#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SunkenCityCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOxygenChanged, float, OxygenPercent);

/**
 * Player character for the Sunken City prototype.
 * Walking/running/jumping use the stock Character/CharacterMovementComponent.
 * Swimming reuses UE's built-in MOVE_Swimming (entered automatically inside a
 * PhysicsVolume with bWaterVolume=true - see AWaterVolumePrototype) together
 * with the engine's built-in swim-up-on-Jump / swim-down-on-Crouch behavior.
 * ADiveZoneVolume marks the fully-submerged sub-regions used for the oxygen system.
 */
UCLASS()
class SUNKENCITY_API ASunkenCityCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASunkenCityCharacter();

	// --- Water / diving ---

	UFUNCTION(BlueprintCallable, Category = "Water")
	void SetSubmerged(bool bNewSubmerged);

	UFUNCTION(BlueprintPure, Category = "Water")
	bool IsSubmerged() const { return bIsSubmerged; }

	UFUNCTION(BlueprintPure, Category = "Water")
	bool IsSwimming() const;

	UFUNCTION(BlueprintPure, Category = "Water")
	float GetOxygenPercent() const { return MaxOxygen > 0.f ? CurrentOxygen / MaxOxygen : 0.f; }

	UPROPERTY(BlueprintAssignable, Category = "Water")
	FOnOxygenChanged OnOxygenChanged;

	UPROPERTY(EditDefaultsOnly, Category = "Water")
	float MaxOxygen = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Water")
	float OxygenDrainRate = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Water")
	float OxygenRecoverRate = 4.f;

	// --- Movement tuning ---

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float WalkSpeed = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float SprintSpeed = 550.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float SwimSpeed = 350.f;

	// --- Interaction ---

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionRange = 250.f;

	UFUNCTION(BlueprintPure, Category = "Interaction")
	FText GetCurrentInteractionPrompt() const { return CurrentInteractionPrompt; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> FootstepSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> SwimSound;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void StartSprint();
	void StopSprint();
	void JumpPressed();
	void DivePressed();
	void DiveReleased();
	void Interact();
	void TakePhoto();

	void UpdateOxygen(float DeltaTime);
	void UpdateInteractionTrace();
	void UpdateFootsteps(float DeltaTime);
	bool TryMantle();

	bool bIsSubmerged = false;
	bool bIsSprinting = false;
	float CurrentOxygen = 20.f;
	float FootstepTimer = 0.f;
	FText CurrentInteractionPrompt;
};
