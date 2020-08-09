// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	NONE,
	PISTOL,
	RIFLE
};

class AItem;
class AWeapon;

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponSlot, AWeapon*> WeaponInventory;
};