// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"

class AWeapon;

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

	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWeapon* EquippedWeapon;
};
