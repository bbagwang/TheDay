// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include <System/TDGameInstance.h>

#pragma region TraceChannel
#define WeaponTraceChannel ECC_GameTraceChannel1
#pragma endregion

#pragma region ObjectChannel
#define InteractionObjectChannel ECC_GameTraceChannel2
#pragma endregion

#pragma region Globals
#define TDGAME_INSTANCE(object) (Cast<UTDGameInstance>(object->GetWorld()->GetGameInstance()))
#define EVENT_MANAGER(object) (TDGAME_INSTANCE(object)->EventManager)
#pragma endregion
