// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDProjectile.generated.h"

UCLASS()
class THEDAY_API ATDProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	ATDProjectile();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
