// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"

class AWeapon;
class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEDAY_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponManagerComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Attack();
	bool CanAttack();

	void UpdateAimPoint();

	FORCEINLINE bool IsAttacking() const { return bAttacking; }
	FORCEINLINE void SetAttacking(bool bNewAttacking) { bAttacking = bNewAttacking; }

	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
	FORCEINLINE void SetEquippedWeapon(AWeapon* NewWeapon) { EquippedWeapon = NewWeapon; }

	FORCEINLINE FVector GetAimPoint() { return AimPoint; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceLength;

	UPROPERTY(BlueprintReadWrite)
	FVector AimPoint;

	UPROPERTY()
	ABaseCharacter* OwnerCharacter;

	FCollisionQueryParams CollQuery;
	FHitResult CameraAimHitResult;
};