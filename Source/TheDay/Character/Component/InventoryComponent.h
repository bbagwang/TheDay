// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Common/CommonEnum.h"
#include "InventoryComponent.generated.h"

class AItem;
class AWeapon;
class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEDAY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region ItemInventory
public:
	//새로운 무기를 추가한다.
	UFUNCTION(BlueprintCallable)
	void AddItem(AItem* NewItem);
	//ItemName 으로 아이템 인벤토리에서 아이템을 찾는다.
	UFUNCTION(BlueprintCallable)
	AItem* GetItemByName(const FName InItemName);
	//ItemName 으로 아이템 인벤토리에서 아이템이 존재하나 확인한다.
	UFUNCTION(BlueprintCallable)
	bool CheckItemByName(const FName InItemName);
	//ItemName 으로 아이템 인벤토리에서 아이템을 삭제한다.
	UFUNCTION(BlueprintCallable)
	void RemoveItemByName(const FName InItemName);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AItem*> ItemInventory;
#pragma endregion

#pragma region WeaponInventory
public:
	//새로운 무기를 추가한다.
	UFUNCTION(BlueprintCallable)
	void AddWeapon(AWeapon* NewWeapon,bool bEquip);
	//무기를 장착한다.
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(EWeaponSlot EquipSlot, bool bInstant = false);
	//무기를 장착 해제한다.
	UFUNCTION(BlueprintCallable)
	void UnEquipWeapon(bool bInstant);
	UFUNCTION(BlueprintCallable)
	void DropWeapon(EWeaponSlot DropSlot);

	//WeaponName 으로 무기 인벤토리에서 무기를 찾는다.
	UFUNCTION(BlueprintCallable)
	AWeapon* GetWeaponByName(const FName InWeaponName);
	//EWeaponSlot 으로 무기 인벤토리에서 무기를 찾는다.
	UFUNCTION(BlueprintCallable)
	AWeapon* GetWeaponBySlot(const EWeaponSlot InSlot);
	//WeaponName 으로 무기 인벤토리에서 무기가 존재하나 확인한다.
	UFUNCTION(BlueprintCallable)
	bool CheckWeaponByName(const FName InWeaponName);
	//EWeaponSlot 으로 무기 인벤토리에서 무기가 존재하나 확인한다.
	UFUNCTION(BlueprintCallable)
	bool CheckWeaponBySlot(const EWeaponSlot InSlot);
	//WeaponName 으로 무기 인벤토리에서 무기를 삭제한다.
	UFUNCTION(BlueprintCallable)
	void RemoveWeaponByName(const FName InWeaponName);
	//EWeaponSlot 으로 무기 인벤토리에서 무기를 삭제한다.
	UFUNCTION(BlueprintCallable)
	void RemoveWeaponBySlot(const EWeaponSlot InSlot);

	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
protected:
	void UpdateWeaponOwnership(AWeapon* InWeapon);
	void UpdateWeaponEquipStatus(AWeapon* InWeapon,bool bEquip);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponSlot, AWeapon*> WeaponInventory;
	UPROPERTY(BlueprintReadWrite)
	AWeapon* EquippedWeapon;
	UPROPERTY()
	ABaseCharacter* OwnerCharacter;
};