// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class THEDAY_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LocalizedName;

public:
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return WeaponMesh; }
	FORCEINLINE FName GetWeaponName() const { return WeaponName; }
	FORCEINLINE FText GetLocalizedName() const { return LocalizedName; }

#pragma region Weapon
public:
	UFUNCTION(BlueprintCallable)
	virtual void Attack();
	UFUNCTION(BlueprintPure)
	virtual bool CanAttack();
protected:
	UFUNCTION(BlueprintCallable)
	virtual void StartAttack();
	UFUNCTION(BlueprintCallable)
	virtual bool EndAttack();
#pragma endregion

#pragma region Aim
public:
	FORCEINLINE bool IsAiming() const { return bIsAiming; }
	FORCEINLINE void SetAiming(bool bNewAiming) { bIsAiming = bNewAiming; }
	FORCEINLINE bool CanAiming() const { return bCanAiming; }
	FORCEINLINE void SetCanAiming(bool bNewCanAiming) { bCanAiming = bNewCanAiming; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAiming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAiming;
#pragma endregion
};