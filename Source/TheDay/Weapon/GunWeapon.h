// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "GunWeapon.generated.h"

UCLASS()
class THEDAY_API AGunWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	AGunWeapon();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
#pragma region Weapon
public:
	virtual void Attack();
	virtual bool CanAttack();
protected:
	virtual void StartAttack();
	virtual bool EndAttack();
#pragma endregion

#pragma region GunWeapon
public:

	UFUNCTION(BlueprintPure)
	FVector CalculateFireStartLocation() const;
	UFUNCTION(BlueprintPure)
	FVector CalculateFireEndLocation() const;

	//void UpdateFireSpread() const;
	//void IncreaseFireSpread() const;
	//void RecoverFireSpread() const;

	FORCEINLINE	FTransform GetMuzzleTransform() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	float BaseDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	float FireRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	float FireSpreadX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	float FireSpreadY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	float FireSpreadIncreaseX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	float FireSpreadIncreaseY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	float FireSpreadRecoveryX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	float FireSpreadRecoveryY;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Debug")
	bool bDEBUG;

	FCollisionQueryParams CollQuery;
private:

#pragma endregion
};
