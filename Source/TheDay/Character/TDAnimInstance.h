// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TDAnimInstance.generated.h"

UCLASS()
class THEDAY_API UTDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTDAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
#pragma region Essential
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Essential")
	class ABaseCharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential")
	FVector Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential")
	FRotator ActorRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential")
	FRotator ControllerRotation;
#pragma endregion

#pragma region Movement
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsMoving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ConfirmMovingThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsSprinting;
#pragma endregion

#pragma region Idle;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	UAnimMontage* Montage_Idle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float IdleTime;
	
	//Idle이 지속될 경우 다른 애니메이션 재생
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle|Breaker")
	UAnimMontage* Montage_Idle_Breaker;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle|Breaker")
	bool bUseIdleBreaker;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle|Breaker")
	float IdleBreakerCallMaxTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle|Breaker")
	float IdleBreakerCallMinTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle|Breaker")
	float CurrentIdleBreakerTargetTime;
#pragma endregion

#pragma region Jump
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	bool bIsJumping;
#pragma endregion

#pragma region Crouch
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")
	bool bIsCrouching;
#pragma endregion

#pragma region Ragdoll
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ragdoll")
	bool bIsRagdoll;
#pragma endregion

#pragma region Aim
protected:
	void CalculateAimOffset(float DeltaSeconds);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	UAnimMontage* Montage_Aim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	float AimYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	float AimPitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	float AimBlendSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	FVector AimPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	FRotator AimPointRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	bool bIsAiming;
#pragma endregion

#pragma region IK
protected:
	void UpdateWeaponIK(float DeltaSeconds);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK")
	FTransform LeftHandIKTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK")
	float LeftHandIKAlpha;
#pragma endregion

#pragma region Item
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class AItem* EquippedItem;
#pragma endregion

#pragma region Weapon
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class AWeapon* EquippedWeapon;
#pragma endregion

#pragma region Attack
public:
	float GetAttackMontageSequenceTime(FName SectionName = TEXT("Default"));

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UAnimMontage* Montage_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool bIsAttacking;
#pragma endregion

#pragma region Dead
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dead")
	bool bIsDying;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dead")
	bool bIsDead;
#pragma endregion

#pragma region Reload
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reload")
	UAnimMontage* Montage_Reload;
#pragma endregion

#pragma region Equip
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip")
	UAnimMontage* Montage_Equip;
#pragma endregion

#pragma region UnEquip
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnEquip")
	UAnimMontage* Montage_UnEquip;
#pragma endregion
};
