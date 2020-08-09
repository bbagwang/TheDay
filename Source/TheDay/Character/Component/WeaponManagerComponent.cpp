// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "WeaponManagerComponent.h"
#include "Weapon/Weapon.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
	return true;
}