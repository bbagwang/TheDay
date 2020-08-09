// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THEDAY_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatusComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Health
public:
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void AddHealth(float AddHealth) { Health += AddHealth; }
	FORCEINLINE void SetHealth(float SetHealth) { Health = SetHealth; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;
#pragma endregion

#pragma region Attack
public:
	FORCEINLINE bool IsAttacking() const { return bAttacking; }
	FORCEINLINE void SetAttacking(bool bNewAttacking) { bAttacking = bNewAttacking; }
	FORCEINLINE bool CanAttack() const { return bCanAttack; }
	FORCEINLINE void SetCanAttack(bool bNewCanAttack) { bCanAttack = bNewCanAttack; }
	FORCEINLINE bool CanBeDamaged() const { return bCanBeDamaged; }
	FORCEINLINE void SetCanBeDamaged(bool bNewCanBeDamaged) { bCanBeDamaged = bNewCanBeDamaged; }
	FORCEINLINE bool CanDoDamage() const { return bCanAttack; }
	FORCEINLINE void SetCanDoDamage(bool bNewCanDoDamage) { bCanDoDamage = bNewCanDoDamage; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeDamaged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanDoDamage;
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