#include "SunkenCityCharacter.h"
#include "SunkenCityGameMode.h"
#include "Interaction/IInteractable.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

ASunkenCityCharacter::ASunkenCityCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MaxSwimSpeed = SwimSpeed;
	GetCharacterMovement()->Buoyancy = 1.02f;
	GetCharacterMovement()->CrouchedHalfHeight = 60.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 60.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ASunkenCityCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentOxygen = MaxOxygen;
}

void ASunkenCityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateOxygen(DeltaTime);
	UpdateInteractionTrace();
	UpdateFootsteps(DeltaTime);
}

void ASunkenCityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASunkenCityCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASunkenCityCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASunkenCityCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASunkenCityCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASunkenCityCharacter::JumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Dive", IE_Pressed, this, &ASunkenCityCharacter::DivePressed);
	PlayerInputComponent->BindAction("Dive", IE_Released, this, &ASunkenCityCharacter::DiveReleased);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASunkenCityCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASunkenCityCharacter::StopSprint);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASunkenCityCharacter::Interact);
	PlayerInputComponent->BindAction("PhotoMode", IE_Pressed, this, &ASunkenCityCharacter::TakePhoto);
}

void ASunkenCityCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
	}
}

void ASunkenCityCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
	}
}

void ASunkenCityCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASunkenCityCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ASunkenCityCharacter::StartSprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	GetCharacterMovement()->MaxSwimSpeed = SwimSpeed * 1.4f;
}

void ASunkenCityCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MaxSwimSpeed = SwimSpeed;
}

void ASunkenCityCharacter::JumpPressed()
{
	// On dry land, try a short mantle over low ledges before falling back to a normal jump.
	if (!IsSwimming() && !GetCharacterMovement()->IsFalling() && TryMantle())
	{
		return;
	}
	// Underwater, the engine's swim physics already move the character up while bPressedJump is true.
	Jump();
}

void ASunkenCityCharacter::DivePressed()
{
	if (IsSwimming())
	{
		// The engine's swim physics move the character down while crouching.
		Crouch();
	}
}

void ASunkenCityCharacter::DiveReleased()
{
	UnCrouch();
}

bool ASunkenCityCharacter::TryMantle()
{
	const FVector Forward = GetActorForwardVector();
	const FVector ActorLoc = GetActorLocation();
	const float HalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	const FVector ForwardStart = ActorLoc + FVector(0.f, 0.f, -HalfHeight * 0.5f);
	const FVector ForwardEnd = ForwardStart + Forward * 60.f;
	FHitResult ForwardHit;
	if (!GetWorld()->LineTraceSingleByChannel(ForwardHit, ForwardStart, ForwardEnd, ECC_Visibility, Params))
	{
		return false;
	}

	const FVector TopStart = ForwardHit.ImpactPoint + Forward * 30.f + FVector(0.f, 0.f, 150.f);
	const FVector TopEnd = TopStart - FVector(0.f, 0.f, 200.f);
	FHitResult TopHit;
	if (!GetWorld()->LineTraceSingleByChannel(TopHit, TopStart, TopEnd, ECC_Visibility, Params))
	{
		return false;
	}

	const float LedgeHeight = TopHit.ImpactPoint.Z - ActorLoc.Z;
	if (LedgeHeight < 40.f || LedgeHeight > 170.f)
	{
		return false;
	}

	const FVector NewLocation = TopHit.ImpactPoint + FVector(0.f, 0.f, HalfHeight + 5.f);
	LaunchCharacter(FVector(0.f, 0.f, 300.f), false, true);
	SetActorLocation(NewLocation, true);
	return true;
}

void ASunkenCityCharacter::Interact()
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (Controller)
	{
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetActorLocation();
		ViewRotation = GetActorRotation();
	}

	const FVector TraceEnd = ViewLocation + ViewRotation.Vector() * InteractionRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, ViewLocation, TraceEnd, ECC_Visibility, Params))
	{
		if (Hit.GetActor() && Hit.GetActor()->Implements<UInteractable>())
		{
			IInteractable::Execute_OnInteract(Hit.GetActor(), this);
		}
	}
}

void ASunkenCityCharacter::TakePhoto()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->ConsoleCommand(TEXT("HighResShot 2"));
	}
}

void ASunkenCityCharacter::SetSubmerged(bool bNewSubmerged)
{
	bIsSubmerged = bNewSubmerged;
}

bool ASunkenCityCharacter::IsSwimming() const
{
	return GetCharacterMovement()->IsSwimming();
}

void ASunkenCityCharacter::UpdateOxygen(float DeltaTime)
{
	const float PreviousOxygen = CurrentOxygen;

	if (bIsSubmerged)
	{
		CurrentOxygen = FMath::Max(0.f, CurrentOxygen - OxygenDrainRate * DeltaTime);
		if (CurrentOxygen <= 0.f)
		{
			if (ASunkenCityGameMode* GM = GetWorld()->GetAuthGameMode<ASunkenCityGameMode>())
			{
				GM->RespawnAtCheckpoint(this);
				CurrentOxygen = MaxOxygen;
			}
		}
	}
	else
	{
		CurrentOxygen = FMath::Min(MaxOxygen, CurrentOxygen + OxygenRecoverRate * DeltaTime);
	}

	if (!FMath::IsNearlyEqual(PreviousOxygen, CurrentOxygen))
	{
		OnOxygenChanged.Broadcast(GetOxygenPercent());
	}
}

void ASunkenCityCharacter::UpdateInteractionTrace()
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (Controller)
	{
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		CurrentInteractionPrompt = FText::GetEmpty();
		return;
	}

	const FVector TraceEnd = ViewLocation + ViewRotation.Vector() * InteractionRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, ViewLocation, TraceEnd, ECC_Visibility, Params) &&
		Hit.GetActor() && Hit.GetActor()->Implements<UInteractable>())
	{
		CurrentInteractionPrompt = IInteractable::Execute_GetInteractionPrompt(Hit.GetActor());
	}
	else
	{
		CurrentInteractionPrompt = FText::GetEmpty();
	}
}

void ASunkenCityCharacter::UpdateFootsteps(float DeltaTime)
{
	const bool bGrounded = !GetCharacterMovement()->IsFalling() && !IsSwimming();
	const float Speed = GetVelocity().Size2D();

	if (Speed < 10.f)
	{
		FootstepTimer = 0.f;
		return;
	}

	FootstepTimer += DeltaTime;
	const float Interval = bIsSprinting ? 0.28f : 0.42f;
	if (FootstepTimer < Interval)
	{
		return;
	}
	FootstepTimer = 0.f;

	USoundBase* SoundToPlay = IsSwimming() ? SwimSound : FootstepSound;
	if (SoundToPlay && (bGrounded || IsSwimming()))
	{
		UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation());
	}
}
