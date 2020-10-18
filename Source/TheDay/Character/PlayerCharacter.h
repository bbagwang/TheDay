// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/MainCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class THEDAY_API APlayerCharacter : public AMainCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	class UInteractionMasterComponent* InteractionMasterComponent;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraSpringArmComponent() const { return SpringArmComponent; }
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
    FORCEINLINE class UInteractionMasterComponent* GetInteractionMasterComponent() const { return InteractionMasterComponent; }

#pragma region Aim
	virtual void Input_StartAiming() override;
	virtual void Input_EndAiming() override;
#pragma endregion

#pragma region Interaction
protected:
    void Input_StartInteraction();
    void Input_EndInteraction();
#pragma endregion

#pragma region FOV
protected:
	void UpdateAimFOV(float DeltaTime);

protected:
	float DefaultFOV;
#pragma endregion
};