// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/WeaponManagerComponent.h"

const FName AWeapon::WeaponMeshName = TEXT("Weapon Mesh");

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CalculateAttackAnimationSpeed();
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region Item
void AWeapon::LoadItemDataFromDataTable()
{
	Super::LoadItemDataFromDataTable();
}
#pragma endregion

#pragma region Attack
void AWeapon::Attack()
{

}

bool AWeapon::CanAttack()
{
	if (!OwnerCharacter)
		return false;

	if (!OwnerCharacter->GetWeaponManagerComponent()->bAttackKeyPressed)
		return false;

	return true;
}

void AWeapon::CalculateAttackAnimationSpeed()
{
	AttackAnimationSpeed = 1.f;
	return;
}

void AWeapon::StartAttack()
{
	bAttacking = true;
}

void AWeapon::EndAttack()
{
	bAttacking = false;
}
#pragma endregion

#pragma region Aim
bool AWeapon::CanAiming()
{
	return true;
}

FVector AWeapon::GetAimingDirection()
{
	if (OwnerCharacter && OwnerCharacter->GetWeaponManagerComponent())
	{
		return OwnerCharacter->GetActorLocation() - OwnerCharacter->GetWeaponManagerComponent()->GetAimPoint();
	}

	return FVector::ZeroVector;
}
#pragma endregion

#pragma region Inventory
void AWeapon::OnTaken()
{
	Super::OnTaken();
}

bool AWeapon::CanTake()
{
	if(!Super::CanTake())
		return false;

	return true;
}
#pragma endregion
