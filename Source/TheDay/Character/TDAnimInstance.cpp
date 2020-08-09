// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TDAnimInstance.h"
#include "BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/StatusComponent.h"

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
	Rotation = OwnerCharacter->GetActorRotation();
	Speed = UKismetMathLibrary::VSize(Velocity);
	Direction = CalculateDirection(Velocity, Rotation);
	bIsMoving = (Speed >= 0.f) ? true : false;
	bIsJumping = OwnerCharacter->GetCharacterMovement()->IsFalling();
	if (OwnerCharacter->GetStatusComponent())
	{
		bIsAiming = OwnerCharacter->GetStatusComponent()->IsAiming();
		bIsAttacking = OwnerCharacter->GetStatusComponent()->IsAttacking();
	}
}
