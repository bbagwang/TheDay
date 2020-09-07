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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

#pragma region Weapon
public:
	virtual void Attack();
	virtual bool CanAttack();
protected:
	virtual void StartAttack();
	virtual bool EndAttack();
#pragma endregion

#pragma region GunWeapon
public:
	UFUNCTION(BlueprintPure)
	FVector CalculateFireStartLocation() const;
	UFUNCTION(BlueprintPure)
	FVector CalculateFireEndLocation() const;


	void SetFireRate(float InFireRate);
	bool CanFire();
	//void UpdateFireSpread() const;
	//void IncreaseFireSpread() const;
	//void RecoverFireSpread() const;

	FORCEINLINE	FTransform GetMuzzleTransform() const;

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
	float FireSpreadX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	float FireSpreadY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	float FireSpreadIncreaseX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	float FireSpreadIncreaseY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	float FireSpreadRecoveryX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire|Spread")
	float FireSpreadRecoveryY;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Sockets")
	FName MuzzleSocketName;

	FCollisionQueryParams CollQuery;
	FTimerHandle FireTimer;
#pragma endregion

#pragma region Effects
protected:
	void PlayFireSound();
	void PlayFireMuzzleEffect();
	void SpawnFireTracerEffect(FVector StartPoint, FVector EndPoint);
	void SpawnImpactEffect(FVector SpawnLocation, FRotator SpawnRotation);
	void PlayFireCamShake();

protected:
	//격발음 사운드 큐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class USoundBase* FireSoundQue;
	//총구 격발 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireMuzzleEffect;
	//맞은 위치 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireImpactEffect;
	//총알 트레이스 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireTracerEffect;
	//격발 카메라 셰이크
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	TSubclassOf<class UCameraShake> FireCamShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	FName TracerParameterName;
#pragma endregion
};