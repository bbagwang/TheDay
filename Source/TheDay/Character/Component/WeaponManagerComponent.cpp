// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "WeaponManagerComponent.h"
#include "Weapon/Weapon.h"
#include "Character/BaseCharacter.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Common/CommonDefinition.h"
#include "DrawDebugHelpers.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	TraceLength = 10000.f;
}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	CollQuery.AddIgnoredActor(OwnerCharacter);
	CollQuery.TraceTag = "Gun Fire Trace";

	if (OwnerCharacter && OwnerCharacter->GetInventoryComponent())
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
	if (EquippedWeapon)
		return true;

	return false;
}

void UWeaponManagerComponent::UpdateAimPoint()
{
	FVector CameraLocation;
	FRotator CameraRotation;

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraViewPoint(CameraLocation, CameraRotation);

	FVector CameraForward = UKismetMathLibrary::GetForwardVector(CameraRotation);
	FVector AimPointTraceEnd = CameraForward * TraceLength;
	GetWorld()->LineTraceSingleByChannel(CameraAimHitResult, CameraLocation, AimPointTraceEnd, WeaponTraceChannel, CollQuery);
	DrawDebugLine(GetWorld(), CameraLocation, AimPointTraceEnd, FColor::Red);
	AimPoint = CameraAimHitResult.Location;
}