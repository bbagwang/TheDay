// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "StatusComponent.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}