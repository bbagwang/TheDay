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
	//ItemName ���� ������ �κ��丮���� �������� ã�´�.
	UFUNCTION(BlueprintCallable)
	AItem* GetItemByName(const FName InItemName);
	//ItemName ���� ������ �κ��丮���� �������� �����ϳ� Ȯ���Ѵ�.
	UFUNCTION(BlueprintCallable)
	bool CheckItemByName(const FName InItemName);
	//ItemName ���� ������ �κ��丮���� �������� �����Ѵ�.
	UFUNCTION(BlueprintCallable)
	void RemoveItemByName(const FName InItemName);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AItem*> ItemInventory;
#pragma endregion

#pragma region WeaponInventory
public:
	//WeaponName ���� ���� �κ��丮���� ���⸦ ã�´�.
	UFUNCTION(BlueprintCallable)
	AWeapon* GetWeaponByName(const FName InWeaponName);
	//EWeaponSlot ���� ���� �κ��丮���� ���⸦ ã�´�.
	UFUNCTION(BlueprintCallable)
	AWeapon* GetWeaponBySlot(const EWeaponSlot InSlot);
	//WeaponName ���� ���� �κ��丮���� ���Ⱑ �����ϳ� Ȯ���Ѵ�.
	UFUNCTION(BlueprintCallable)
	bool CheckWeaponByName(const FName InWeaponName);
	//EWeaponSlot ���� ���� �κ��丮���� ���Ⱑ �����ϳ� Ȯ���Ѵ�.
	UFUNCTION(BlueprintCallable)
	bool CheckWeaponBySlot(const EWeaponSlot InSlot);
	//WeaponName ���� ���� �κ��丮���� ���⸦ �����Ѵ�.
	UFUNCTION(BlueprintCallable)
	void RemoveWeaponByName(const FName InWeaponName);
	//EWeaponSlot ���� ���� �κ��丮���� ���⸦ �����Ѵ�.
	UFUNCTION(BlueprintCallable)
	void RemoveWeaponBySlot(const EWeaponSlot InSlot);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponSlot, AWeapon*> WeaponInventory;
};