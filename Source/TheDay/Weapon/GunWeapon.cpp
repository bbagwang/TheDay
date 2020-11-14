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
#include "Components/AudioComponent.h"
#include "System/TDBlueprintFunctionLibrary.h"

static int32 DebugWeaponLineTrace = 0;
FAutoConsoleVariableRef CVARDebugWeaponLineTrace(TEXT("td.debugWeaponlinetrace"), DebugWeaponLineTrace, TEXT("Draw Weapon Debug"), ECVF_Cheat);

const FName AGunWeapon::MuzzleSoundComponentName = TEXT("Muzzle Sound");
const FName AGunWeapon::MuzzleEffectComponentName = TEXT("Muzzle Effect");

AGunWeapon::AGunWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MuzzleSoundComponent = CreateDefaultSubobject<UAudioComponent>(MuzzleSoundComponentName);
	ensure(MuzzleSoundComponent);
	MuzzleSoundComponent->SetupAttachment(ItemMesh, MuzzleSocketName);

	MuzzleEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(MuzzleEffectComponentName);
	ensure(MuzzleEffectComponent);
	MuzzleEffectComponent->SetupAttachment(ItemMesh, MuzzleSocketName);

	TracerParameterName = "Target";

	if (bWEAPON_DEBUG)
	{
		DebugWeaponLineTrace = 1;
	}
}

void AGunWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();

	CollQuery.AddIgnoredActor(this);
	CollQuery.AddIgnoredActor(OwnerCharacter);
	CollQuery.bTraceComplex = true;
	CollQuery.bReturnPhysicalMaterial = true;
	CollQuery.TraceTag = "Gun Fire Trace";

	ensure(FireSoundQue);
	MuzzleSoundComponent->SetSound(FireSoundQue);

	ensure(FireMuzzleEffect);
	MuzzleEffectComponent->SetTemplate(FireMuzzleEffect);
	MuzzleEffectComponent->DeactivateSystem();

	ensure(FireMontage);
	//ensure(ReloadMontage);

	SetFireRate(FireRate);
}

void AGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!OwnerCharacter)
		return;

	UpdateFireSpread();
}

#pragma region Item
void AGunWeapon::LoadItemDataFromDataTable()
{
	Super::LoadItemDataFromDataTable();
}
#pragma endregion

#pragma region Attack
void AGunWeapon::Attack()
{
	StartAttack();
}

bool AGunWeapon::CanAttack()
{
	if (!Super::CanAttack())
		return false;

	if (!CanFire())
		return false;

	return true;
}

void AGunWeapon::CalculateAttackAnimationSpeed()
{
	if (!OwnerCharacter || !FireMontage)
	{
		AttackAnimationSpeed = 1.f;
		return;
	}

	float CurrentAttackSectionTime = FireMontage->GetSectionLength(FireMontage->GetSectionIndex(TEXT("Default")));
	AttackAnimationSpeed = (TimeBetweenShots > 0.f) ? CurrentAttackSectionTime / TimeBetweenShots : 1.f;
}

void AGunWeapon::StartAttack()
{
	Super::StartAttack();

	UE_LOG(LogTemp, Warning, TEXT("StartAttack"));
	bAttacking = true;
	CalculateAttackAnimationSpeed();
	StartFire();
}

void AGunWeapon::EndAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("EndAttack"));
	EndFire();

	Super::EndAttack();
}
#pragma endregion

#pragma region GunWeapon
void AGunWeapon::StartFire()
{
	PlayFireMontage();
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
	FireCountFromStart = 0;
	StopRepeatFireTimer();
	StopFireSound();
	StopFireMontage();
}

void AGunWeapon::Fire()
{
	if (!CanAttack())
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
	SpawnEjectShellEffect();
	IncreaseFireSpread();

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
	GetWorldTimerManager().SetTimer(FireTimer, this, &AGunWeapon::Fire, TimeBetweenShots, true, FireDelay);
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
	if (!bInfiniteAmmoMode && (CurrentMagazine <= 0 || CurrentAmmo <= 0))
		return false;

	if (FireMode == EGunWeaponFireMode::BURST && FireCountFromStart >= BurstFireCount)
		return false;

	return true;
}

void AGunWeapon::UpdateFireSpread()
{
	//State Check
	//Idle, Walk, Sprint, Crouch, Jump

	//FireSpreadMin = TODOCalculate();
	//FireSpreadMax = TODOCalculate();

	RecoverFireSpread();
	EVENT_MANAGER(this)->UpdateBulletSpread(FireSpread);
}

void AGunWeapon::IncreaseFireSpread()
{
	//State Check
	//Idle, Walk, Sprint, Crouch, Jump
	FireSpread += FireSpreadIncrease;
	FireSpread = UTDBlueprintFunctionLibrary::Vector2DClamp(FireSpread, FireSpreadMin, FireSpreadMax);
}

void AGunWeapon::RecoverFireSpread()
{
	//State Check
	//Idle, Walk, Sprint, Crouch, Jump
	FireSpread -= FireSpreadRecovery;
	FireSpread = UTDBlueprintFunctionLibrary::Vector2DClamp(FireSpread, FireSpreadMin, FireSpreadMax);
}
#pragma endregion

#pragma region Aim
bool AGunWeapon::CanAiming()
{
	return true;
}

FVector AGunWeapon::GetAimingDirection()
{
	if (OwnerCharacter && OwnerCharacter->GetWeaponManagerComponent())
	{
		return GetMuzzleLocation() - OwnerCharacter->GetWeaponManagerComponent()->GetAimPoint();
	}

	return Super::GetAimingDirection();
}
#pragma endregion

#pragma region Effects
void AGunWeapon::PlayFireSound()
{
	if (!FireSoundQue)
		return;

	if (FireMode == EGunWeaponFireMode::FULL_AUTO)
	{
		if (MuzzleSoundComponent->IsPlaying())
			return;
	}

	MuzzleSoundComponent->Play();
}

void AGunWeapon::StopFireSound()
{
	if (FireMode == EGunWeaponFireMode::FULL_AUTO)
	{
		if (MuzzleSoundComponent->IsPlaying())
			MuzzleSoundComponent->Stop();
	}
}

void AGunWeapon::PlayFireMuzzleEffect()
{
	if (!MuzzleEffectComponent || !FireMuzzleEffect || !MuzzleEffectComponent->Template)
		return;

	MuzzleEffectComponent->ActivateSystem();
}

void AGunWeapon::SpawnFireTracerEffect(FVector StartPoint, FVector EndPoint)
{
	if (!FireTracerEffect)
		return;

	UParticleSystemComponent* TracerComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireTracerEffect, StartPoint);

	if (!TracerComponent)
		return;

	//Bullet Tracer 관련 파라메터
	TracerComponent->SetVectorParameter(TracerParameterName, EndPoint);
}

void AGunWeapon::PlayFireCamShake()
{
	if (!OwnerCharacter)
		return;
	//플레이어가 아닐시 리턴
	if (!OwnerCharacter->IsPlayerControlled())
		return;

	ATDPlayerController* PC = Cast<ATDPlayerController>(OwnerCharacter->GetController());

	if (!PC)
		return;

	PC->ClientPlayCameraShake(FireCamShakeClass);
}

void AGunWeapon::SpawnImpactEffect(FVector SpawnLocation, FRotator SpawnRotation)
{
	if (!FireImpactEffect)
		return;

	//TODO : Make Impact Spawner
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireImpactEffect, SpawnLocation, SpawnRotation);
}

void AGunWeapon::SpawnEjectShellEffect()
{
	FVector EjectShellLocation;
	FRotator EjectShellRotation;
	ItemMesh->GetSocketWorldLocationAndRotation(EjectShellSocketName, EjectShellLocation, EjectShellRotation);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EjectShellEffect, EjectShellLocation, EjectShellRotation);
}
#pragma endregion

#pragma region Montage
void AGunWeapon::PlayFireMontage()
{
	if (ItemMesh && FireMontage)
	{
		UAnimInstance* ItemAnimInstance = ItemMesh->GetAnimInstance();
		if (ItemAnimInstance)
		{
			ItemAnimInstance->Montage_Play(FireMontage, AttackAnimationSpeed);

			////Loop
			//FName CurrentSection = ItemAnimInstance->Montage_GetCurrentSection(FireMontage);
			//ItemAnimInstance->Montage_SetNextSection(CurrentSection, CurrentSection, FireMontage);
		}
	}
}

void AGunWeapon::StopFireMontage()
{
	if (ItemMesh && FireMontage)
	{
		UAnimInstance* ItemAnimInstance = ItemMesh->GetAnimInstance();
		if (ItemAnimInstance)
		{
			ItemAnimInstance->Montage_Stop(0.f, FireMontage);
		}
	}
}

void AGunWeapon::PlayReloadMontage()
{

}
#pragma endregion

#pragma region Inventory
void AGunWeapon::OnTaken()
{
	Super::OnTaken();
}

bool AGunWeapon::CanTake()
{
	if (!Super::CanTake())
		return false;

	return true;
}
#pragma endregion