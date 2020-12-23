// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Component/StatusComponent.h"
#include "Component/InventoryComponent.h"
#include "Component/WeaponManagerComponent.h"
#include "Component/TDCharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "System/TDPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Common/CommonNameSpace.h"

const FName ABaseCharacter::StatusComponentName = TEXT("Status Component");
const FName ABaseCharacter::InventoryComponentName = TEXT("Inventory Component");
const FName ABaseCharacter::WeaponManagerComponentName = TEXT("Weapon Manager Component");

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UTDCharacterMovementComponent>(CharacterMovementComponentName))
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	 
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanFly = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanJump = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanSwim = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanWalk = true;

    StatusComponent = CreateDefaultSubobject<UStatusComponent>(StatusComponentName);
    ensure(StatusComponent);
    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(InventoryComponentName);
    ensure(InventoryComponent);
    WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponent>(WeaponManagerComponentName);
    ensure(WeaponManagerComponent);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	//Control
	PlayerInputComponent->BindAction(InputKeyName::JUMP, IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(InputKeyName::JUMP, IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(InputKeyName::CROUCH, IE_Pressed, this, &ABaseCharacter::Input_StartCrouch);
	PlayerInputComponent->BindAction(InputKeyName::CROUCH, IE_Released, this, &ABaseCharacter::Input_EndCrouch);
	PlayerInputComponent->BindAction(InputKeyName::SPRINT, IE_Pressed, this, &ABaseCharacter::Input_StartSprint);
	PlayerInputComponent->BindAction(InputKeyName::SPRINT, IE_Released, this, &ABaseCharacter::Input_EndSprint);
	//Combat
	PlayerInputComponent->BindAction(InputKeyName::AIM, IE_Pressed, this, &ABaseCharacter::Input_StartAiming);
	PlayerInputComponent->BindAction(InputKeyName::AIM, IE_Released, this, &ABaseCharacter::Input_EndAiming);
	PlayerInputComponent->BindAction(InputKeyName::ATTACK, IE_Pressed, this, &ABaseCharacter::Input_StartAttack);
	PlayerInputComponent->BindAction(InputKeyName::ATTACK, IE_Released, this, &ABaseCharacter::Input_EndAttack);
	

	//Control
	PlayerInputComponent->BindAxis(InputKeyName::MOVE_FORWARD, this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(InputKeyName::MOVE_RIGHT, this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis(InputKeyName::TURN, this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(InputKeyName::TURN_RATE, this, &ABaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis(InputKeyName::LOOKUP, this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(InputKeyName::LOOKUP_RATE, this, &ABaseCharacter::LookUpAtRate);
}

void ABaseCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::Input_StartAiming()
{
	if (!GetWeaponManagerComponent())
		return;

	GetWeaponManagerComponent()->SetAiming(true);
}

void ABaseCharacter::Input_EndAiming()
{
	if (!GetWeaponManagerComponent())
		return;

	GetWeaponManagerComponent()->SetAiming(false);
}
#pragma endregion

#pragma region Crouch
void ABaseCharacter::Input_StartCrouch()
{
	Crouch();
}

void ABaseCharacter::Input_EndCrouch()
{
	UnCrouch();
}

void ABaseCharacter::Input_StartSprint()
{
	if (GetTDCharacterMovement())
		GetTDCharacterMovement()->SetSprint(true);
}

void ABaseCharacter::Input_EndSprint()
{
	if (GetTDCharacterMovement())
		GetTDCharacterMovement()->SetSprint(false);
}

FString ABaseCharacter::GenerateAttackMontageSectionName()
{
	FString SectionName;
	if (GetTDCharacterMovement()&&GetTDCharacterMovement()->IsCrouching())
		SectionName.Append(TEXT("Crouch"));
	else
		SectionName.Append(TEXT("Stand"));

	return SectionName;
}

#pragma endregion

#pragma region Attack
void ABaseCharacter::Input_StartAttack()
{
    if (!WeaponManagerComponent)
        return;

    WeaponManagerComponent->bAttackKeyPressed = true;
    WeaponManagerComponent->Attack();
}

void ABaseCharacter::Input_EndAttack()
{
    if (!WeaponManagerComponent)
        return;

    WeaponManagerComponent->bAttackKeyPressed = false;
}
#pragma endregion

#pragma region Dead
void ABaseCharacter::Dead(bool bInstantDead, bool bRagdollMode /*= true*/)
{
    StartDead(bInstantDead, bRagdollMode);
}

void ABaseCharacter::StartDead(bool bInstantDead, bool bRagdollMode /*= true*/)
{
	GetTDCharacterMovement()->StopMovementImmediately();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ATDPlayerController* PC = Cast<ATDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
	{
		EndDead();
		return;
	}
	//Anim Processing
	if (bInstantDead)
	{
		EndDead();
	}
}

void ABaseCharacter::EndDead()
{
	if (!StatusComponent)
		return;

}
#pragma endregion