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

#pragma region Character
	UPROPERTY()
	ABaseCharacter* OwnerCharacter;
#pragma endregion

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