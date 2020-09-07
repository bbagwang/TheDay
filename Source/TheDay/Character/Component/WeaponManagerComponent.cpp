// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "WeaponManagerComponent.h"
#include "Weapon/Weapon.h"
#include "Character/BaseCharacter.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Common/CommonDefinition.h"
#include "DrawDebugHelpers.h"
#include "../PlayerCharacter.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	TraceLength = 10000.f;
	
	AimFOV = 45.f;
	AimInterpSpeed = 20.f;

}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	if (!OwnerCharacter)
		return;

	CollQuery.AddIgnoredActor(OwnerCharacter);
	CollQuery.TraceTag = "Gun Fire Trace";

	if (OwnerCharacter->GetInventoryComponent())
	{
		EquippedWeapon = OwnerCharacter->GetInventoryComponent()->GetEquippedWeapon();
	}

}

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateAimPoint();	
}

void UWeaponManagerComponent::Attack()
{
	if (!CanAttack())
		return;

	EquippedWeapon->Attack();
}

bool UWeaponManagerComponent::CanAttack()
{
	//Character Condition Check
	if (!EquippedWeapon)
		return false;

	return true;
}

void UWeaponManagerComponent::UpdateAimPoint()
{
	FVector CameraLocation;
	FRotator CameraRotation;

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraViewPoint(CameraLocation, CameraRotation);

	FVector CameraForward = UKismetMathLibrary::GetForwardVector(CameraRotation);
	FVector AimPointTraceEnd = CameraLocation + CameraForward * TraceLength;
	GetWorld()->LineTraceSingleByChannel(CameraAimHitResult, CameraLocation, AimPointTraceEnd, WeaponTraceChannel, CollQuery);
	AimPoint = CameraAimHitResult.bBlockingHit ? CameraAimHitResult.Location : CameraAimHitResult.TraceEnd;
}

void UWeaponManagerComponent::SetAiming(bool bNewAiming)
{
	bIsAiming = bNewAiming;

	OwnerCharacter->bUseControllerRotationYaw = bIsAiming;
	OwnerCharacter->GetTDCharacterMovement()->bOrientRotationToMovement = !bIsAiming;

	bIsAiming ? StartAiming() : EndAiming();
}

bool UWeaponManagerComponent::CanAiming()
{
	//TODO
	return true;
}

void UWeaponManagerComponent::StartAiming()
{
	if (!OwnerCharacter)
		return;

	if (!CanAiming())
	{
		EndAiming();
		return;
	}
	
	bIsAiming = true;
}

void UWeaponManagerComponent::EndAiming()
{
	//TODO
	bIsAiming = false;
}
