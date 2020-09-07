// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TDAnimInstance.h"
#include "BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/StatusComponent.h"
#include "Component/WeaponManagerComponent.h"

UTDAnimInstance::UTDAnimInstance()
{

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
	Rotation = OwnerCharacter->GetActorRotation();
	Direction = CalculateDirection(Velocity, Rotation);

	bIsMoving = (Speed >= 0.f) ? true : false;
	bIsJumping = OwnerCharacter->GetTDCharacterMovement()->IsFalling();
	bIsCrouching = OwnerCharacter->GetTDCharacterMovement()->IsCrouching();

	if (OwnerCharacter->GetWeaponManagerComponent())
	{
		bIsAttacking = OwnerCharacter->GetWeaponManagerComponent()->IsAttacking();
		bIsAiming = OwnerCharacter->GetWeaponManagerComponent()->IsAiming();
	}
}