// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CommonEnum.generated.h"

#pragma region Inventory

#pragma region Inventory Weapon
UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	NONE,
	MELEE,
	SMALL,
	MEDIUM
};
#pragma endregion

#pragma endregion

#pragma region Weapon
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
#pragma endregion

#pragma region Interaction
//UENUM(BlueprintType)
//enum class EInteractionWidgetStyle : uint8
//{
//	
//};
#pragma endregion