// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "TDGameInstance.h"
#include "Kismet/GameplayStatics.h"

UTDGameInstance::UTDGameInstance()
{
	SlowMotionRate = 0.3f;
}

void UTDGameInstance::Init()
{
	Super::Init();
	InitInstances();
}

void UTDGameInstance::OnStart()
{
	Super::OnStart();
}

void UTDGameInstance::InitInstances()
{
	ensure(EventManagerClass);
	EventManager = NewObject<UTDEventManager>(EventManagerClass);
	ensure(EventManager);
}

void UTDGameInstance::SetSlowMotion(bool bActive, float SlowMotionRateOverride /*= 0.3f*/)
{
	if (SlowMotionRate == SlowMotionRateOverride)
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), SlowMotionRate);
	else
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), SlowMotionRateOverride);
}
