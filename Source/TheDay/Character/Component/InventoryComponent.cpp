// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "InventoryComponent.h"
#include "Item/Item.h"
#include "Weapon/Weapon.h"
#include "Character/BaseCharacter.h"
#include "WeaponManagerComponent.h"
#include "Common/CommonNameSpace.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

#pragma region ItemInventory
void UInventoryComponent::AddItem(AItem* NewItem)
{

}

AItem* UInventoryComponent::GetItemByName(const FName InItemName)
{
	for (AItem* Iter : ItemInventory)
	{
		if (!Iter)
			continue;

		if (Iter->GetItemName().IsEqual(InItemName) && !Iter->IsPendingKill())
			return Iter;
		else
			return nullptr;
	}
	return nullptr;
}

bool UInventoryComponent::CheckItemByName(const FName InItemName)
{
	return (GetItemByName(InItemName) != nullptr) ? true : false;
}

void UInventoryComponent::RemoveItemByName(const FName InItemName)
{
	AItem* RemoveCandidate = GetItemByName(InItemName);
	if (RemoveCandidate)
		RemoveCandidate->Destroy();
	else
		UE_LOG(LogTemp, Error, TEXT("Can't Remove Item Name : %s"), *InItemName.ToString());
}
#pragma endregion

#pragma region WeaponInventory
void UInventoryComponent::AddWeapon(AWeapon* NewWeapon, bool bEquip)
{
	if (!NewWeapon)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Add Weapon. Weapon Not Exist!"));
		return;
	}

	EWeaponType NewWeaponType = NewWeapon->GetWeaponType();
	EWeaponSlot NewWeaponSlot = GetWeaponSlotByWeaponType(NewWeaponType);

	if (WeaponInventory.Find(NewWeaponSlot))
	{
		AWeapon* DropWeaponCandidate = WeaponInventory[NewWeaponSlot];
		DropWeapon(NewWeaponSlot);
	}

	UpdateWeaponOwnership(NewWeapon);

	WeaponInventory.Add(NewWeaponSlot, NewWeapon);

	if (bEquip)
		EquipWeapon(NewWeaponSlot);
}

void UInventoryComponent::EquipWeapon(EWeaponSlot EquipSlot, bool bInstant /*= false*/)
{
	//ANIM NOTIFIED
	if (!WeaponInventory.Find(EquipSlot))
	{
		return;
	}
	AWeapon* EquipCandidate = GetWeaponBySlot(EquipSlot);
	if (!EquipCandidate)
		return;

	EquippedWeapon = EquipCandidate;

	if (OwnerCharacter && OwnerCharacter->GetWeaponManagerComponent())
	{
		OwnerCharacter->GetWeaponManagerComponent()->SetEquippedWeapon(EquippedWeapon);
		
		EquippedWeapon->SetOwnerCharacter(OwnerCharacter);
		EquippedWeapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, CharacterSocketName::HAND_R_SOCKET);
	}
}

void UInventoryComponent::UnEquipWeapon(bool bInstant)
{
	//ANIM NOTIFIED
	EquippedWeapon = nullptr;
}

void UInventoryComponent::DropWeapon(EWeaponSlot DropSlot)
{
	//TODO : DROP IT
}

AWeapon* UInventoryComponent::GetWeaponByName(const FName InWeaponName)
{
	for (TPair<EWeaponSlot, AWeapon*> Iter : WeaponInventory)
	{
		if (!Iter.Value)
			continue;

		AWeapon* WeaponCandidate = Iter.Value;
		if (WeaponCandidate->GetWeaponName().IsEqual(InWeaponName))
			return WeaponCandidate;
		else
			continue;
	}
	return nullptr;
}

AWeapon* UInventoryComponent::GetWeaponBySlot(const EWeaponSlot InSlot)
{
	AWeapon** WeaponCandidate = WeaponInventory.Find(InSlot);
	return *WeaponCandidate;
}

bool UInventoryComponent::CheckWeaponByName(const FName InWeaponName)
{
	return (GetWeaponByName(InWeaponName) != nullptr) ? true : false;
}

bool UInventoryComponent::CheckWeaponBySlot(const EWeaponSlot InSlot)
{
	return (GetWeaponBySlot(InSlot) != nullptr) ? true : false;
}

void UInventoryComponent::RemoveWeaponByName(const FName InWeaponName)
{
	AWeapon* RemoveCandidate = GetWeaponByName(InWeaponName);
	if (RemoveCandidate)
	{
		const EWeaponSlot* WeaponKey = WeaponInventory.FindKey(RemoveCandidate);
		if (WeaponKey && *WeaponKey != EWeaponSlot::NONE)
		{
			WeaponInventory.Remove(*WeaponKey);
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Can't Remove Weapon Name : %s"), *InWeaponName.ToString());
}

void UInventoryComponent::RemoveWeaponBySlot(const EWeaponSlot InSlot)
{
	//TODO : 현재 무기 체크
	WeaponInventory.Remove(InSlot);
}

EWeaponSlot UInventoryComponent::GetWeaponSlotByWeaponType(const EWeaponType InWeaponType)
{
	switch (InWeaponType)
	{
	case EWeaponType::PISTOL:
		return EWeaponSlot::SMALL;
		break;
	case EWeaponType::RIFLE:
	case EWeaponType::SNIPER:
	case EWeaponType::SHOTGUN:
		return EWeaponSlot::MEDIUM;
		break;
	case EWeaponType::ONE_HAND_MELEE:
		return EWeaponSlot::MELEE;
		break;
	case EWeaponType::TWO_HANDS_MELEE:
		return EWeaponSlot::MELEE;
		break;

	case EWeaponType::NONE:
	default:
		return EWeaponSlot::NONE;
		break;
	}
}

void UInventoryComponent::UpdateWeaponOwnership(AWeapon* InWeapon)
{
	if (!InWeapon || !OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Find Weapon To Update Ownership!"));
		return;
	}

	InWeapon->SetOwner(OwnerCharacter);
	InWeapon->SetInstigator(OwnerCharacter);
}

void UInventoryComponent::UpdateWeaponEquipStatus(AWeapon* InWeapon, bool bEquip)
{
	if (!InWeapon || !OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Find Weapon To Update Equip Status!"));
		return;
	}

	InWeapon->SetActorTickEnabled(bEquip);
	InWeapon->SetActorHiddenInGame(!bEquip);
}

#pragma endregion