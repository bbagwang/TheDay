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
	//�� �߾� ���
	SEMI_AUTO,
	//N �߾� ���
	BURST,
	//���� ���
	FULL_AUTO,
	//����, ��Ʈ �׼� ���
	PULL_ACTION
};