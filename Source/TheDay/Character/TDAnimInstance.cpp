// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TDAnimInstance.h"
#include "BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/StatusComponent.h"
#include "Component/WeaponManagerComponent.h"
#include "Component/InventoryComponent.h"
#include "Common/CommonNameSpace.h"

UTDAnimInstance::UTDAnimInstance()
{
	//Essenstial
	OwnerCharacter = nullptr;

	Velocity = FVector();
	Speed = 0.f;
	Direction = 0.f;
	ActorRotation = FRotator();

	ControllerRotation = FRotator();

	//Movement
	bIsMoving = false;
	ConfirmMovingThreshold = 10.f;
	bIsSprinting = false;

	//Idle
	Montage_Idle = nullptr;
	IdleTime = 0.f;

	Montage_Idle_Breaker = nullptr;
	bUseIdleBreaker = true;
	IdleBreakerCallMaxTime = 20.f;
	IdleBreakerCallMinTime = 15.f;
	CurrentIdleBreakerTargetTime = 0.f;

	//Jump
	bIsJumping = false;

	//Crouch
	bIsCrouching = false;

	//Ragdoll
	bIsRagdoll = false;

	//Aim
	Montage_Aim = nullptr;
	AimYaw = 0.f;
	AimPitch = 0.f;
	AimBlendSpeed = 0.15f;
	Montage_Aim = nullptr;
	bIsAiming = false;

	//IK
	LeftHandIKTransform.SetIdentity();
	LeftHandIKAlpha = 1.f;

	//Item
	EquippedItem = nullptr;

	//Weapon
	EquippedWeapon = nullptr;

	//Attack
	Montage_Attack = nullptr;
	bIsAttacking = false;

	//Dead
	bIsDying = false;
	bIsDead = false;

	//Reload
	Montage_Reload = nullptr;
	
	//Equip
	Montage_Equip = nullptr;

	//UnEquip
	Montage_UnEquip = nullptr;
}

void UTDAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	ensure(OwnerCharacter);
}

void UTDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!OwnerCharacter) return;
	
	Velocity = OwnerCharacter->GetVelocity();
	Speed = UKismetMathLibrary::VSize(Velocity);
	ActorRotation = OwnerCharacter->GetActorRotation();
	Direction = CalculateDirection(Velocity, ActorRotation);
	
	ControllerRotation = OwnerCharacter->GetControlRotation();

	bIsMoving = (Speed >= ConfirmMovingThreshold) ? true : false;
	
	if (OwnerCharacter->GetInventoryComponent())
	{
		UInventoryComponent* Inventory = OwnerCharacter->GetInventoryComponent();

		//TODO : 아이템 관련 설정
		EquippedItem = Inventory->GetEquippedItem();
	}

	if (OwnerCharacter->GetTDCharacterMovement())
	{
		UTDCharacterMovementComponent* TDMovement = OwnerCharacter->GetTDCharacterMovement();

		bIsSprinting = TDMovement->IsSprinting();
		bIsJumping = TDMovement->IsFalling();
		bIsCrouching = TDMovement->IsCrouching();
	}
	
	if (OwnerCharacter->GetStatusComponent())
	{
		UStatusComponent* StatusManager = OwnerCharacter->GetStatusComponent();

		bIsRagdoll = StatusManager->IsRagdollMode();
		bIsDying = StatusManager->IsDying();
		bIsDead = StatusManager->IsDead();
	}

	if (OwnerCharacter->GetWeaponManagerComponent())
	{
		UWeaponManagerComponent* WeaponManager = OwnerCharacter->GetWeaponManagerComponent();

		bIsAiming = WeaponManager->IsAiming();
		AimPoint = WeaponManager->GetAimPoint();
		bIsAttacking = WeaponManager->IsAttacking();
		EquippedWeapon = WeaponManager->GetEquippedWeapon();
	}

	if (EquippedWeapon)
	{
		AimPointRotator = EquippedWeapon->GetAimingDirection().Rotation();
	}

	CalculateAimOffset(DeltaSeconds);
	UpdateWeaponIK(DeltaSeconds);
}

#pragma region Aim
void UTDAnimInstance::CalculateAimOffset(float DeltaSeconds)
{
	FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(ControllerRotation, ActorRotation);
	FRotator CurrentAORotation = FRotator(AimPitch, AimYaw, 0.f);
	FRotator InterpRotation = UKismetMathLibrary::RInterpTo(CurrentAORotation, DeltaRotation, DeltaSeconds, 15.f);
	AimYaw = UKismetMathLibrary::ClampAngle(InterpRotation.Yaw, -90.f, 90.f);
	AimPitch = UKismetMathLibrary::ClampAngle(InterpRotation.Pitch, -90.f, 90.f);
}

void UTDAnimInstance::UpdateWeaponIK(float DeltaSeconds)
{
	if(!OwnerCharacter)
		return;

	if (!EquippedWeapon)
		return;

	USkeletalMeshComponent* WeaponMesh = EquippedWeapon->GetItemMesh();
	if (!WeaponMesh)
		return;

	FTransform LeftHandSocketTransform = WeaponMesh->GetSocketTransform(WeaponSocketName::LEFT_HAND_IK_SOCKET,ERelativeTransformSpace::RTS_World);
	FVector BonespaceLocation;
	FRotator BonespaceRotation;
	OwnerCharacter->GetMesh()->TransformToBoneSpace(CharacterBoneName::HAND_R, LeftHandSocketTransform.GetLocation(), LeftHandSocketTransform.GetRotation().Rotator(),BonespaceLocation,BonespaceRotation);
	LeftHandIKTransform = FTransform(BonespaceRotation,BonespaceLocation);
}

#pragma endregion

#pragma region Attack
float UTDAnimInstance::GetAttackMontageSequenceTime(FName SectionName /*= TEXT("Default")*/)
{
	if (!Montage_Attack)
		return 0.f;

	//TODO : 애니메이션이 2개 이상/ 섹션이 2개 이상일 경우 새로운 계산식이 필요함
	if (!ensure(Montage_Attack->IsValidSectionName(SectionName)))
		return 0.f;

	int32 SectionIndex = Montage_Attack->GetSectionIndex(SectionName);

	float AttackMontageLength = Montage_Attack->GetSectionLength(SectionIndex);

	return AttackMontageLength;
}

#pragma endregion
