// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TheDayGameMode.h"
#include "TheDayCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheDayGameMode::ATheDayGameMode()
{
}

void ATheDayGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UE_LOG(LogTemp, Warning, TEXT("Init Game!"));
}
