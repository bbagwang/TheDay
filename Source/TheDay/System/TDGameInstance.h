// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TDEventManager.h"
#include "TDGameInstance.generated.h"

UCLASS(BlueprintType, Blueprintable)
class THEDAY_API UTDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTDGameInstance();

protected:
	void Init() override;
	void OnStart() override;

private:
	void InitInstances();

#pragma region SlowMotion
public:
	UFUNCTION(BlueprintCallable)
	void SetSlowMotion(bool bActive, float SlowMotionRateOverride = 0.3f);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlowMotionRate;
#pragma endregion

#pragma region EventManager
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTDEventManager> EventManagerClass;
	UPROPERTY(BlueprintReadOnly)
	UTDEventManager* EventManager;
#pragma endregion

};
