// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "InventoryComponent.h"
#include "Item/Item.h"
#include "Weapon/Weapon.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

#pragma region ItemInventory
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
	WeaponInventory.Remove(InSlot);
}
#pragma endregion