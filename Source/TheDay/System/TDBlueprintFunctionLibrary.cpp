// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TDBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TDCameraManager.h"
#include "Character/PlayerCharacter.h"
#include "TDGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

UTDBlueprintFunctionLibrary::UTDBlueprintFunctionLibrary()
{

}

ATDCameraManager* UTDBlueprintFunctionLibrary::GetTDCameraManager(UObject* WorldContext)
{
	ATDCameraManager* TDCameraManager = Cast<ATDCameraManager>(UGameplayStatics::GetPlayerCameraManager(WorldContext->GetWorld(), 0));

	return TDCameraManager;
}

APlayerCharacter* UTDBlueprintFunctionLibrary::GetPlayerCharacter(UObject* WorldContext)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContext->GetWorld(), 0));

	return PlayerCharacter;
}

class UTDGameInstance* UTDBlueprintFunctionLibrary::GetTDGameInstance(UObject* WorldContext)
{
	UTDGameInstance* TDGameInstnace = Cast<UTDGameInstance>(UGameplayStatics::GetGameInstance(WorldContext));
	
	return TDGameInstnace;
}

FVector2D UTDBlueprintFunctionLibrary::Vector2DClamp(FVector2D Current, FVector2D Min, FVector2D Max)
{
	Current.X = FMath::Clamp(Current.X, Min.X, Max.X);
	Current.Y = FMath::Clamp(Current.Y, Min.Y, Max.Y);

	return Current;
}
