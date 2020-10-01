// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

namespace CharacterBoneName
{
	static const FName HAND_L = TEXT("hand_l");
	static const FName HAND_R = TEXT("hand_r");
}

namespace CharacterSocketName
{
	static const FName HAND_L_SOCKET = TEXT("hand_l_Socket");
	static const FName HAND_R_SOCKET = TEXT("hand_r_Socket");
}

namespace WeaponSocketName
{
	static const FName LEFT_HAND_IK_SOCKET = TEXT("LeftHandIKSocket");
}

namespace InputKeyName
{
	//ACTION
	static const FName JUMP = TEXT("Jump");
	static const FName CROUCH = TEXT("Crouch");
	static const FName SPRINT = TEXT("Sprint");
	static const FName AIM = TEXT("Aim");
	static const FName ATTACK = TEXT("Attack");
	static const FName INTERACTION = TEXT("Interaction");

	//SPECIAL ACTION
	static const FName ESC = TEXT("Escape");

	//AXIS
	static const FName MOVE_FORWARD = TEXT("MoveForward");
	static const FName MOVE_RIGHT = TEXT("MoveRight");
	static const FName TURN = TEXT("Turn");
	static const FName TURN_RATE = TEXT("TurnRate");
	static const FName LOOKUP = TEXT("LookUp");
	static const FName LOOKUP_RATE = TEXT("LookUpRate");
	
}