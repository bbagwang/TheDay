// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/TDCharacterMovementComponent.h"
#include "TDAnimInstance.h"
#include "BaseCharacter.generated.h"

class UStatusComponent;
class UInventoryComponent;
class UWeaponManagerComponent;
class UTDCharacterMovementComponent;

UCLASS(config=Game)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
	friend UStatusComponent;

public:
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void MoveForward(float Value);
	void MoveRight(float Value);

public:
	FORCEINLINE UStatusComponent* GetStatusComponent() { return StatusComponent; }
	FORCEINLINE UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
	FORCEINLINE UWeaponManagerComponent* GetWeaponManagerComponent() { return WeaponManagerComponent; }
	FORCEINLINE UTDCharacterMovementComponent* GetTDCharacterMovement() { return Cast<UTDCharacterMovementComponent>(GetCharacterMovement()); }
	FORCEINLINE UTDAnimInstance* GetTDAnimInstance() { return GetMesh() ? Cast<UTDAnimInstance>(GetMesh()->GetAnimInstance()) : nullptr; }

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
protected:
	virtual void Input_StartAiming();
	virtual void Input_EndAiming();
#pragma endregion

#pragma region Crouch
protected:
	virtual void Input_StartCrouch();
	virtual void Input_EndCrouch();
#pragma endregion

#pragma region Sprint
protected:
	virtual void Input_StartSprint();
	virtual void Input_EndSprint();
#pragma endregion

#pragma region Attack
public:
	virtual FString GenerateAttackMontageSectionName();

protected:
	virtual void Input_StartAttack();
	virtual void Input_EndAttack();
#pragma endregion

#pragma region Interaction
protected:
	virtual void Input_StartInteraction();
	virtual void Input_EndInteraction();
#pragma endregion

#pragma region Death
public:
	void Dead(bool bInstantDead, bool bRagdollMode = true);

protected:
	void StartDead(bool bInstantDead, bool bRagdollMode = true);
	void EndDead();

#pragma endregion
};