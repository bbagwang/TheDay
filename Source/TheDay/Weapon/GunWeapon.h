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
	//�⺻ ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	float BaseDamage;
	//�д� �߻�� (RPM)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	float FireRate;
	//�߻� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	float FireRange;
	//������ Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	TSubclassOf<UDamageType> DamageType;
	//�߻� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	EGunWeaponFireMode FireMode;
	
	//Burst Fire Mode �� ��� �� ��ݴ� �߻��� ź�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Fire")
	int32 BurstFireCount;

	//����� ������ �������� �߻��� ź���� ����
	UPROPERTY(BlueprintReadOnly)
	int32 FireCountFromStart;

	float LastFiredTime;
	float TimeBetweenShots;

	//���� źâ�� ź�� ���� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Ammo")
	int32 CurrentMagazine;
	//�ִ� źâ�� ź�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Ammo")
	int32 MaxMagazine;
	//���� ź�� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Ammo")
	int32 CurrentAmmo;
	//�ִ� ź�� ���� ����
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
	//�ݹ��� ���� ť
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class USoundBase* FireSoundQue;
	//�ѱ� �ݹ� ����Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireMuzzleEffect;
	//���� ��ġ ����Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireImpactEffect;
	//�Ѿ� Ʈ���̽� ����Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireTracerEffect;
	//�ݹ� ī�޶� ����ũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	TSubclassOf<class UCameraShake> FireCamShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	FName TracerParameterName;
#pragma endregion
};