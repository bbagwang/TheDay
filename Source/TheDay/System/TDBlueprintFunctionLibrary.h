// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TDBlueprintFunctionLibrary.generated.h"

UCLASS()
class THEDAY_API UTDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UTDBlueprintFunctionLibrary();

	UFUNCTION(BlueprintCallable)
	static class ATDCameraManager* GetTDCameraManager(UObject* WorldContext);

	UFUNCTION(BlueprintCallable)
	static class APlayerCharacter* GetPlayerCharacter(UObject* WorldContext);

	UFUNCTION(BlueprintCallable)
	static class UTDGameInstance* GetTDGameInstance(UObject* WorldContext);

	UFUNCTION(BlueprintCallable)
	static FVector2D Vector2DClamp(FVector2D Current, FVector2D Min, FVector2D Max);
};
