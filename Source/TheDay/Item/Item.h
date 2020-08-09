// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class THEDAY_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
