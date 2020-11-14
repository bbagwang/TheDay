// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/TDCharacterMovementComponent.h"
#include "TDAnimInstance.h"
#include "BaseCharacter.generated.h"

class UInventoryComponent;
class UWeaponManagerComponent;
class UTDCharacterMovementComponent;
class UInteractionComponent;
class UTDAnimInstance;

UCLASS(config=Game)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
	
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
	FORCEINLINE UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
	FORCEINLINE UWeaponManagerComponent* GetWeaponManagerComponent() { return WeaponManagerComponent; }
	FORCEINLINE UTDCharacterMovementComponent* GetTDCharacterMovement() { return Cast<UTDCharacterMovementComponent>(GetCharacterMovement()); }
    FORCEINLINE UInteractionComponent* GetInteractionComponent() { return InteractionComponent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UInventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWeaponManagerComponent* WeaponManagerComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UInteractionComponent* InteractionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

#pragma region Health
public:
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void SetHealth(float NewHealth) { Health = NewHealth; OnHealthChanged(NewHealth, true);}
	FORCEINLINE void IncreaseHealth(float Amount) { Health += Amount; OnHealthChanged(Amount); }
	FORCEINLINE void DecreaseHealth(float Amount) { Health -= Amount; OnHealthChanged(-Amount); }

protected:
	virtual void OnHealthChanged(float ChangeAmount, bool bChangeBySet = false);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;
#pragma endregion

#pragma region Damage
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	bool ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const override;
#pragma endregion

#pragma region Animation
public:
	FORCEINLINE UTDAnimInstance* GetTDAnimInstance() { return AnimInstance; }

protected:
	UPROPERTY()
	UTDAnimInstance* AnimInstance;
#pragma endregion

#pragma region Montage
public:
	void PlayAttackMontage(float PlayRate = 1.f, FName SectionName = NAME_None);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAnimMontage* DeadMontage;
#pragma endregion
	
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
	//TODO : Deprecated and Implement on Weapon Manager
	virtual FString GenerateAttackMontageSectionName();

protected:
	virtual void Input_StartAttack();
	virtual void Input_EndAttack();
#pragma endregion

#pragma region Dead
public:
	virtual bool NeedDead();
	virtual bool CanDead();
	
	void Dead(bool bInstantDead, bool bRagdollMode = true);

	FORCEINLINE bool IsDead() const { return bDead; }
	FORCEINLINE bool IsDying() const { return bDying; }
	FORCEINLINE bool IsDyingorDead() const { return bDying || bDead; }

protected:
	virtual void StartDead(bool bInstantDead, bool bRagdollMode = true);
	virtual void EndDead();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDead;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDying;
#pragma endregion

#pragma region Ragdoll
public:
	void RagdollMode(bool bActiveRagdoll) { bActiveRagdoll ? StartRagdollMode() : EndRagdollMode(); }

	FORCEINLINE bool IsRagdollMode() const { return bIsRagdollMode; }

protected:
	virtual void StartRagdollMode();
	virtual void EndRagdollMode();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsRagdollMode;
#pragma endregion

#pragma region Names
protected:
    static const FName StatusComponentName;
    static const FName InventoryComponentName;
    static const FName WeaponManagerComponentName;
    static const FName InteractionComponentName;
#pragma endregion
};