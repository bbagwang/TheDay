// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TDCharacterMovementComponent.h"

UTDCharacterMovementComponent::UTDCharacterMovementComponent()
{
	NavAgentProps.bCanCrouch = true;
	NavAgentProps.bCanFly = true;
	NavAgentProps.bCanJump = true;
	NavAgentProps.bCanSwim = true;
	NavAgentProps.bCanWalk = true;
	
	GetNavAgentPropertiesRef().bCanCrouch = true;
	GetNavAgentPropertiesRef().bCanFly = true;
	GetNavAgentPropertiesRef().bCanJump = true;
	GetNavAgentPropertiesRef().bCanSwim = true;
	GetNavAgentPropertiesRef().bCanWalk = true;

}

void UTDCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTDCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}