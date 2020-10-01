// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/Weapon.h"
#include "WeaponManagerComponent.generated.h"

class ABaseCharacter;
class AWeapon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEDAY_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponManagerComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Wepaon
public:
	void Attack();
	bool CanAttack();
	
	//공격중인지
	FORCEINLINE bool IsAttacking();
	//현재 착용중인 무기
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
	//착용 무기 설정
	FORCEINLINE void SetEquippedWeapon(AWeapon* NewWeapon) { EquippedWeapon = NewWeapon; }
	//현재 조준중인 위치 가져옴
	FORCEINLINE FVector GetAimPoint() { return AimPoint; }

public:
	//공격키 눌렸는가
	bool bAttackKeyPressed;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AWeapon> StartEquipItemClass;

	UPROPERTY(BlueprintReadOnly)
	bool bCanAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimPointTraceLength;

	UPROPERTY(BlueprintReadOnly)
	FVector AimPoint;

	UPROPERTY()
	ABaseCharacter* OwnerCharacter;

	FCollisionQueryParams CollQuery;
	FHitResult CameraAimHitResult;
#pragma endregion

#pragma region Aim
public:
	void SetAiming(bool bNewAiming);
	bool CanAiming();

	FORCEINLINE bool IsAiming() const { return bIsAiming; }

protected:
	void StartAiming();
	void EndAiming();

	void UpdateAimPoint();

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsAiming;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFullyAiming;
#pragma endregion

#pragma region FOV
public:

	FORCEINLINE float GetAimFOV() const { return AimFOV; }
	FORCEINLINE float GetAimInterpSpeed() const { return AimInterpSpeed; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimInterpSpeed;
#pragma endregion
};