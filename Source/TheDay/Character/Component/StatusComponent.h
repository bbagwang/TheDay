// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

class ABaseCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THEDAY_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatusComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	ABaseCharacter* OwnerCharacter;

#pragma region Character	
public:
	FORCEINLINE bool IsRagdollMode() const { return bIsRagdollMode; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRagdollMode;
#pragma endregion

#pragma region Health
public:
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void SetHealth(float NewHealth) { Health = NewHealth; }
	FORCEINLINE void IncreaseHealth(float Amount) { Health += Amount; }
	FORCEINLINE void DecreaseHealth(float Amount) { Health -= Amount; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;
#pragma endregion

#pragma region Dead
public:
	FORCEINLINE bool IsDead() const { return bDead; }
	FORCEINLINE bool IsDying() const { return bDying; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDying;
#pragma endregion

#pragma region Attack
public:
	FORCEINLINE bool CanBeDamaged() const { return bCanBeDamaged; }
	FORCEINLINE void SetCanBeDamaged(bool bNewCanBeDamaged) { bCanBeDamaged = bNewCanBeDamaged; }
	FORCEINLINE bool CanDoDamage() const { return bCanDoDamage; }
	FORCEINLINE void SetCanDoDamage(bool bNewCanDoDamage) { bCanDoDamage = bNewCanDoDamage; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeDamaged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanDoDamage;
#pragma endregion
};