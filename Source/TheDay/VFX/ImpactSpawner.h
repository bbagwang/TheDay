// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImpactSpawner.generated.h"

UCLASS()
class THEDAY_API AImpactSpawner : public AActor
{
	GENERATED_BODY()

public:
	AImpactSpawner();

	void SpawnImpact(FHitResult& HitResult);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
