// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "MainCharacter.h"

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
