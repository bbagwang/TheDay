// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonStruct.generated.h"

#pragma region Interaction
USTRUCT(BlueprintType)
struct FInteractionWidgetBaseData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanInteract;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LocalizedDisplayText;
};

#pragma endregion