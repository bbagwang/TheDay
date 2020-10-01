// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "ImpactSpawner.h"

AImpactSpawner::AImpactSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

void AImpactSpawner::SpawnImpact(FHitResult& HitResult)
{
	//HitResult.PhysMaterial;
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld())
}

void AImpactSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AImpactSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}