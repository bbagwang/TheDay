// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Common/CommonEnum.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class THEDAY_API AWeapon : public AItem
{
	GENERATED_BODY()

public:	
	AWeapon();
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

#pragma region Item
protected:
	virtual void LoadItemDataFromDataTable() override;
#pragma endregion

#pragma region Debug
protected:
	//무기 디버그
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWEAPON_DEBUG;
#pragma endregion

#pragma region Weapon
public:
	UFUNCTION(BlueprintCallable)
	virtual void Attack();
	UFUNCTION(BlueprintPure)
	virtual bool CanAttack();

	virtual void CalculateAttackAnimationSpeed();

	//공격 상태 반환
	FORCEINLINE bool IsAttacking() const { return bAttacking; }
	//무기 슬롯 반환
	FORCEINLINE EWeaponSlot GetWeaponSlot() const { return WeaponSlot; }
	FORCEINLINE float GetAttackAnimationSpeed() const { return AttackAnimationSpeed; }

protected:
	UFUNCTION(BlueprintCallable)
	virtual void StartAttack();
	UFUNCTION(BlueprintCallable)
	virtual void EndAttack();

protected:
	//무기 슬롯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponSlot WeaponSlot;

	UPROPERTY(BlueprintReadOnly)
	bool bAttacking;
	UPROPERTY(BlueprintReadOnly)
	float AttackAnimationSpeed;

#pragma endregion

#pragma region Aim
public:
	virtual bool CanAiming();
	virtual FVector GetAimingDirection();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AimSpeed;
#pragma endregion

#pragma region Inventory
public:
	virtual void OnTaken() override;
	virtual bool CanTake() override;
#pragma endregion

#pragma region Names
protected:
	static const FName WeaponMeshName;
#pragma endregion
};