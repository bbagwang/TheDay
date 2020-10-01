// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDEventManager.generated.h"

//Åº ÆÛÁü ¾÷µ¥ÀÌÆ®
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBulletSpreadUpdateDelegate, FVector2D, BulletSpread);

UCLASS(BlueprintType, Blueprintable)
class THEDAY_API UTDEventManager : public UObject
{
	GENERATED_BODY()
	
public:
	UTDEventManager();

#pragma region UI
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateBulletSpread(FVector2D BulletSpread);

	FBulletSpreadUpdateDelegate BulletSpreadUpdate;
#pragma endregion
};
