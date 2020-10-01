// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class THEDAY_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	AMeleeWeapon();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

#pragma region Item
protected:
	void LoadItemDataFromDataTable() override;
#pragma endregion

#pragma region Weapon
public:
	void Attack() override;
	bool CanAttack() override;
	void CalculateAttackAnimationSpeed() override;

protected:
	void StartAttack() override;
	void EndAttack() override;
#pragma endregion

#pragma region Aim
	bool CanAiming() override;
	FVector GetAimingDirection() override;
#pragma endregion

#pragma region Inventory
	void OnTaken() override;
	bool CanTake() override;
#pragma endregion
};
