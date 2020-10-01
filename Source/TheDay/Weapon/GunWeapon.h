// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Common/CommonEnum.h"
#include "GunWeapon.generated.h"

UCLASS()
class THEDAY_API AGunWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	AGunWeapon();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

#pragma region Item
protected:
	virtual void LoadItemDataFromDataTable() override;
#pragma endregion

#pragma region Weapon
public:
	virtual void Attack();
	virtual bool CanAttack();

	virtual void CalculateAttackAnimationSpeed() override;

protected:
	virtual void StartAttack();
	virtual void EndAttack();
#pragma endregion

#pragma region GunWeapon
public:
	UFUNCTION(BlueprintPure)
	FVector CalculateFireStartLocation() const;
	UFUNCTION(BlueprintPure)
	FVector CalculateFireEndLocation() const;

	void SetFireRate(float InFireRate);
	bool CanFire();

	void UpdateFireSpread();
	void IncreaseFireSpread();
	void RecoverFireSpread();

	FORCEINLINE FTransform GetMuzzleTransform() const { return ItemMesh->GetSocketTransform(MuzzleSocketName); }
	FORCEINLINE	FVector GetMuzzleLocation() const { return ItemMesh->GetSocketLocation(MuzzleSocketName); }

protected:
	virtual void StartFire();
	virtual void EndFire();
	virtual void Fire();

	void StartRepeatFireTimer();
	void StopRepeatFireTimer();

protected:
	//기본 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	float BaseDamage;
	//분당 발사수 (RPM)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	float FireRate;
	//발사 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	float FireRange;
	//데미지 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	TSubclassOf<UDamageType> DamageType;
	//발사 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	EGunWeaponFireMode FireMode;
	
	//Burst Fire Mode 의 경우 한 사격당 발사할 탄약 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	int32 BurstFireCount;

	//사격을 시작한 시점부터 발사한 탄약의 갯수
	UPROPERTY(BlueprintReadOnly)
	int32 FireCountFromStart;

	float LastFiredTime;
	float TimeBetweenShots;

	//현재 탄창속 탄약 갯수 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Ammo")
	int32 CurrentMagazine;
	//최대 탄창속 탄약 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Ammo")
	int32 MaxMagazine;
	//현재 탄약 보유 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Ammo")
	int32 CurrentAmmo;
	//최대 탄약 보유 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	FVector2D FireSpread;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	FVector2D FireSpreadMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	FVector2D FireSpreadMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	FVector2D FireSpreadIncrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	FVector2D FireSpreadRecovery;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Sockets")
	FName MuzzleSocketName;

	//무한 총알 모드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Cheat")
	bool bInfiniteAmmoMode;

	FCollisionQueryParams CollQuery;
	FTimerHandle FireTimer;
#pragma endregion

#pragma region Aim
public:
	virtual bool CanAiming() override;
	virtual FVector GetAimingDirection() override;
#pragma endregion

#pragma region Sounds
protected:
	void PlayFireSound();
	void StopFireSound();

protected:
	//총구 사운드 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Sound")
	class UAudioComponent* MuzzleSoundComponent;
	//격발음 사운드 큐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Sound")
	class USoundBase* FireSoundQue;
#pragma endregion

#pragma region CameraShake
protected:
	void PlayFireCamShake();

protected:
	//격발 카메라 셰이크
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Camera Shake")
	TSubclassOf<class UCameraShake> FireCamShakeClass;
#pragma endregion

#pragma region Effect
protected:
	void PlayFireMuzzleEffect();
	void SpawnFireTracerEffect(FVector StartPoint, FVector EndPoint);
	void SpawnImpactEffect(FVector SpawnLocation, FRotator SpawnRotation);

protected:
	//총구 이펙트 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystemComponent* MuzzleEffectComponent;
	//총구 격발 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireMuzzleEffect;
	//맞은 위치 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireImpactEffect;
	//총알 트레이스 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireTracerEffect;
	//총알 트레이스 이펙트 관련 파라메터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	FName TracerParameterName;
#pragma endregion

#pragma region Inventory
public:
	virtual void OnTaken() override;
	virtual bool CanTake() override;
#pragma endregion

#pragma region Names
protected:
	static const FName MuzzleEffectComponentName;
	static const FName MuzzleSoundComponentName;

#pragma endregion
};