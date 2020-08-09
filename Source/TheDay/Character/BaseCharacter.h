// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UStatusComponent;
class UInventoryComponent;
class UWeaponManagerComponent;

UCLASS(config=Game)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
		
public:
	ABaseCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UStatusComponent* GetStatusComponent() { return StatusComponent; }
	FORCEINLINE UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
	FORCEINLINE UWeaponManagerComponent* GetWeaponManagerComponent() { return WeaponManagerComponent; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void MoveForward(float Value);
	void MoveRight(float Value);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStatusComponent* StatusComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UInventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWeaponManagerComponent* WeaponManagerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

#pragma region Aim
	void StartAiming();
	void EndAiming();
#pragma endregion
};