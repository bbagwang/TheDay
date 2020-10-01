// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "MeleeWeapon.h"

AMeleeWeapon::AMeleeWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

void AMeleeWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region Weapon
void AMeleeWeapon::Attack()
{
}

bool AMeleeWeapon::CanAttack()
{
	if(!Super::CanAttack())
		return false;

	return true;
}

void AMeleeWeapon::CalculateAttackAnimationSpeed()
{
}

void AMeleeWeapon::StartAttack()
{
}

void AMeleeWeapon::EndAttack()
{
}
#pragma endregion

#pragma region Aim

bool AMeleeWeapon::CanAiming()
{
	return true;
}

FVector AMeleeWeapon::GetAimingDirection()
{
	return Super::GetAimingDirection();
}

void AMeleeWeapon::OnTaken()
{
}

bool AMeleeWeapon::CanTake()
{
	if (!Super::CanTake())
		return false;

	return true;
}

void AMeleeWeapon::LoadItemDataFromDataTable()
{
}