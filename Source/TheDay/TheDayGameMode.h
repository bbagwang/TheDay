// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheDayGameMode.generated.h"

UCLASS(minimalapi)
class ATheDayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheDayGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

};