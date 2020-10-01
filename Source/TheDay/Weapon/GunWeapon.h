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

	//���� �Ѿ� ���
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
	//�ѱ� ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Sound")
	class UAudioComponent* MuzzleSoundComponent;
	//�ݹ��� ���� ť
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Sound")
	class USoundBase* FireSoundQue;
#pragma endregion

#pragma region CameraShake
protected:
	void PlayFireCamShake();

protected:
	//�ݹ� ī�޶� ����ũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Camera Shake")
	TSubclassOf<class UCameraShake> FireCamShakeClass;
#pragma endregion

#pragma region Effect
protected:
	void PlayFireMuzzleEffect();
	void SpawnFireTracerEffect(FVector StartPoint, FVector EndPoint);
	void SpawnImpactEffect(FVector SpawnLocation, FRotator SpawnRotation);

protected:
	//�ѱ� ����Ʈ ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystemComponent* MuzzleEffectComponent;
	//�ѱ� �ݹ� ����Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireMuzzleEffect;
	//���� ��ġ ����Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireImpactEffect;
	//�Ѿ� Ʈ���̽� ����Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Weapon|Effects")
	class UParticleSystem* FireTracerEffect;
	//�Ѿ� Ʈ���̽� ����Ʈ ���� �Ķ����
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