// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDPlayerController.generated.h"

UCLASS()
class THEDAY_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATDPlayerController();
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

#pragma region Input
	void Input_StartEscape();
	void Input_EndEscape();

	UFUNCTION(BlueprintImplementableEvent)
	void Receive_Input_StartEscape();
	UFUNCTION(BlueprintImplementableEvent)
	void Receive_Input_EndEscape();
#pragma endregion
};
