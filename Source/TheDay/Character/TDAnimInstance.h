// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TDAnimInstance.generated.h"

class ABaseCharacter;

UCLASS()
class THEDAY_API UTDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTDAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAiming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsJumping;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsMoving;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage_Aim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABaseCharacter* OwnerCharacter;
};
