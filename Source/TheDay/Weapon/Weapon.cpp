// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/WeaponManagerComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

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

void AWeapon::StartAttack()
{

}

bool AWeapon::EndAttack()
{
	return true;
}
