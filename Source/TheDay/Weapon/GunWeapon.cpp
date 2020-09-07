// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "GunWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Common/CommonDefinition.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/BaseCharacter.h"
#include "Character/Component/WeaponManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "System/TDPlayerController.h"
#include "Camera/CameraShake.h"
#include "Particles/ParticleSystemComponent.h"

static int32 DebugWeaponLineTrace = 0;
FAutoConsoleVariableRef CVARDebugWeaponLineTrace(TEXT("td.debugWeaponlinetrace"), DebugWeaponLineTrace, TEXT("Draw Weapon Debug"), ECVF_Cheat);

AGunWeapon::AGunWeapon()
{

	TracerParameterName = "Target";
}

void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();

	CollQuery.AddIgnoredActor(this);
	CollQuery.AddIgnoredActor(OwnerCharacter);
	CollQuery.bTraceComplex = true;
	CollQuery.bReturnPhysicalMaterial = true;
	CollQuery.TraceTag = "Gun Fire Trace";

	SetFireRate(FireRate);
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
	if (!Super::CanAttack())
		return false;

	return true;
}

void AGunWeapon::StartAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("StartAttack"));

	StartFire();
}

bool AGunWeapon::EndAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("EndAttack"));
	FireCountFromStart = 0;
	EndFire();
	return true;
}

#pragma region GunWeapon
void AGunWeapon::StartFire()
{

	switch (FireMode)
	{
	case EGunWeaponFireMode::SEMI_AUTO:
	case EGunWeaponFireMode::PULL_ACTION:
		Fire();
		break;
	case EGunWeaponFireMode::BURST:
	case EGunWeaponFireMode::FULL_AUTO:
		StartRepeatFireTimer();
		break;

	case EGunWeaponFireMode::NONE:
	default:
		break;
	}
}

void AGunWeapon::EndFire()
{
	StopRepeatFireTimer();
}

void AGunWeapon::Fire()
{
	if (!CanFire())
	{
		EndAttack();
		return;
	}
	FHitResult HitResult;
	FVector FireStart = CalculateFireStartLocation();
	FVector FireEnd = CalculateFireEndLocation();
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, FireStart, FireEnd, WeaponTraceChannel, CollQuery);

	PlayFireMuzzleEffect();
	PlayFireSound();
	PlayFireCamShake();
	SpawnFireTracerEffect(HitResult.TraceStart, bIsHit ? HitResult.ImpactPoint : HitResult.TraceEnd);

	if (bIsHit)
	{
		SpawnImpactEffect(HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
	
		ATDPlayerController* PC = Cast<ATDPlayerController>(OwnerCharacter->GetController());
		UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), BaseDamage, HitResult.TraceEnd - HitResult.TraceStart, HitResult, PC ? PC : nullptr, this, DamageType);
	}

	if (DebugWeaponLineTrace > 0)
	{
		FHitResult DebugHit;
		TArray<AActor*> Ignores;
		ETraceTypeQuery TraceQuery = UEngineTypes::ConvertToTraceType(WeaponTraceChannel);
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), FireStart, FireEnd, TraceQuery, true, Ignores, EDrawDebugTrace::ForDuration, DebugHit, true);
	}

	FireCountFromStart++;
	LastFiredTime = GetWorld()->GetTimeSeconds();
}

void AGunWeapon::StartRepeatFireTimer()
{
	float FireDelay = LastFiredTime + TimeBetweenShots - GetWorld()->GetTimeSeconds();
	FireDelay = FMath::Max(FireDelay, 0.f);
	GetWorldTimerManager().SetTimer(FireTimer, this, &AGunWeapon::Fire,TimeBetweenShots, true, FireDelay);
}

void AGunWeapon::StopRepeatFireTimer()
{
	GetWorldTimerManager().ClearTimer(FireTimer);
}

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

void AGunWeapon::SetFireRate(float InFireRate)
{
	FireRate = InFireRate;
	TimeBetweenShots = 60.f / FireRate;
}

bool AGunWeapon::CanFire()
{
	if (!CanAttack())
		return false;

	if (CurrentMagazine < 0 || CurrentAmmo < 0)
		return false;

	if (FireMode==EGunWeaponFireMode::BURST && FireCountFromStart >= BurstFireCount)
		return false;

	return true;
}

FTransform AGunWeapon::GetMuzzleTransform() const
{
	//추후 소음기 같은게 달리면 Muzzle Transform이 다른 위치일 수 있음
	return WeaponMesh->GetSocketTransform(MuzzleSocketName);
}
#pragma endregion

#pragma region Effects
void AGunWeapon::PlayFireSound()
{
	if (!FireSoundQue)
		return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundQue, CalculateFireStartLocation());
}

void AGunWeapon::PlayFireMuzzleEffect()
{
	if (!FireMuzzleEffect)
		return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireMuzzleEffect, GetMuzzleTransform());
}

void AGunWeapon::SpawnFireTracerEffect(FVector StartPoint, FVector EndPoint)
{
	if (!FireTracerEffect)
		return;

	UParticleSystemComponent* TracerComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireTracerEffect, StartPoint);

	if (!TracerComponent)
		return;

	TracerComponent->SetVectorParameter(TracerParameterName, EndPoint);
}

void AGunWeapon::PlayFireCamShake()
{
	if (!OwnerCharacter)
		return;

	ATDPlayerController* PC = Cast<ATDPlayerController>(OwnerCharacter->GetController());

	if (!PC)
		return;

	PC->ClientPlayCameraShake(FireCamShakeClass);
}

void AGunWeapon::SpawnImpactEffect(FVector SpawnLocation, FRotator SpawnRotation)
{
	if (!FireMuzzleEffect)
		return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireMuzzleEffect, GetMuzzleTransform());
}
#pragma endregion