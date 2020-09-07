// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CommonEnum.generated.h"

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	NONE,
	MELEE,
	SMALL,
	MEDIUM
};

UENUM(BlueprintType)
enum class EGunWeaponType : uint8
{
	NONE,
	PISTOL,
	RIFLE,
	SHOTGUN,
	SNIPER,
};

UENUM(BlueprintType)
enum class EGunWeaponFireMode : uint8
{
	NONE,
	//한 발씩 사격
	SEMI_AUTO,
	//N 발씩 사격
	BURST,
	//연속 사격
	FULL_AUTO,
	//펌프, 볼트 액션 사격
	PULL_ACTION
};