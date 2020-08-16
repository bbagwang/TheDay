// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "GunWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Common/CommonDefinition.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/WeaponManagerComponent.h"

AGunWeapon::AGunWeapon()
{

}

void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();

	CollQuery.bTraceComplex = true;
	CollQuery.bReturnPhysicalMaterial = true;
	CollQuery.TraceTag = "Gun Fire Trace";
}

void AGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunWeapon::Attack()
{
	if (CanAttack())
		StartAttack();
}

bool AGunWeapon::CanAttack()
{
	return true;
}

void AGunWeapon::StartAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("StartAttack"));
	FHitResult HitResult;
	FVector FireStart = CalculateFireStartLocation();
	FVector FireEnd = CalculateFireEndLocation();
	GetWorld()->LineTraceSingleByChannel(HitResult, FireStart, FireEnd, WeaponTraceChannel, CollQuery);
	
	if (bDEBUG)
	{
		FHitResult DebugHit;
		TArray<AActor*> Ignores;
		ETraceTypeQuery TraceQuery = UEngineTypes::ConvertToTraceType(WeaponTraceChannel);
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), FireStart, FireEnd, TraceQuery, true, Ignores, EDrawDebugTrace::ForDuration, DebugHit, true);
	}
}

bool AGunWeapon::EndAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("EndAttack"));
	return true;
}

#pragma region GunWeapon

FVector AGunWeapon::CalculateFireStartLocation() const
{
	return GetMuzzleTransform().GetLocation();
}

FVector AGunWeapon::CalculateFireEndLocation() const
{
	FVector AimLocation;
	if (OwnerCharacter)
		AimLocation = OwnerCharacter->GetWeaponManagerComponent()->GetAimPoint();
	/*FTransform MuzzleTransform = GetMuzzleTransform();
	FVector SpreadNormal = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(MuzzleTransform.GetRotation().GetForwardVector(), FireSpreadY, FireSpreadX);
	return SpreadNormal * FireRange;*/

	return AimLocation;
}

FTransform AGunWeapon::GetMuzzleTransform() const
{
	//추후 소음기 같은게 달리면 Muzzle Transform이 다른 위치일 수 있음
	return WeaponMesh->GetSocketTransform(MuzzleSocketName);
}
#pragma endregion