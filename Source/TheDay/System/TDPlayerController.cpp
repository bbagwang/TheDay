// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TDPlayerController.h"
#include "Common/CommonNameSpace.h"

ATDPlayerController::ATDPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATDPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATDPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction(InputKeyName::ESC, IE_Pressed, this, &ATDPlayerController::Input_StartEscape);
	InputComponent->BindAction(InputKeyName::ESC, IE_Released, this, &ATDPlayerController::Input_EndEscape);
}

#pragma region Input
void ATDPlayerController::Input_StartEscape()
{

	Receive_Input_StartEscape();
}

void ATDPlayerController::Input_EndEscape()
{

	Receive_Input_EndEscape();
}
#pragma endregion