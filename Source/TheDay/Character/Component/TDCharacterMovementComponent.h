// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TDCharacterMovementComponent.generated.h"

UCLASS()
class THEDAY_API UTDCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UTDCharacterMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

#pragma region Move
public:
	FORCEINLINE bool IsSprinting() const { return bSprinting; }
	FORCEINLINE void SetSprint(bool bSprint);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultWalkMaxSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultSprintMaxSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultCrouchMaxSpeed;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bSprinting;

#pragma region
};
