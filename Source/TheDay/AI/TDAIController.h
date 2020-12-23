// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TDAIController.generated.h"

UCLASS()
class THEDAY_API ATDAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATDAIController(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
