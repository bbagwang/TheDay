// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TDGameMode.h"
#include "Character/BaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATDGameMode::ATDGameMode()
{

}

void ATDGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UE_LOG(LogTemp, Warning, TEXT("Init Game!"));
}
