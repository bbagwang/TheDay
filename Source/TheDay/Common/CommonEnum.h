// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CommonEnum.generated.h"

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	NONE,
	MELEE,
	SMALL,
	MEDIUM,
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	NONE,
	PISTOL,
	RIFLE,
	SNIPER,
	SHOTGUN,
	ONE_HAND_MELEE,
	TWO_HANDS_MELEE
};