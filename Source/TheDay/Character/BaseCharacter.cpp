// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Component/InventoryComponent.h"
#include "Component/WeaponManagerComponent.h"
#include "Component/TDCharacterMovementComponent.h"
#include "Item/Component/InteractionComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "System/TDPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Common/CommonNameSpace.h"

const FName ABaseCharacter::InventoryComponentName = TEXT("Inventory Component");
const FName ABaseCharacter::WeaponManagerComponentName = TEXT("Weapon Manager Component");
const FName ABaseCharacter::InteractionComponentName = TEXT("Interaction Component");

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

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(InventoryComponentName);
	ensure(InventoryComponent);
	WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponent>(WeaponManagerComponentName);
	ensure(WeaponManagerComponent);
	InteractionComponent = CreateOptionalDefaultSubobject<UInteractionComponent>(InteractionComponentName);
	if (InteractionComponent)
		InteractionComponent->SetupAttachment(GetMesh());
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UTDAnimInstance>(GetMesh()->GetAnimInstance());
	ensure(AnimInstance);
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

#pragma region Health
void ABaseCharacter::OnHealthChanged(float ChangeAmount, bool bChangeBySet /*= false*/)
{

}
#pragma endregion

#pragma region Damage
float ABaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	DecreaseHealth(Damage);

	return Damage;
}

bool ABaseCharacter::ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const
{
	return Super::ShouldTakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

}

void ABaseCharacter::PlayAttackMontage(float PlayRate /*= 1.f*/, FName SectionName /*= NAME_None*/)
{
	PlayAnimMontage(AttackMontage, PlayRate, SectionName);
}

#pragma endregion

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
	if (GetTDCharacterMovement() && GetTDCharacterMovement()->IsCrouching())
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
bool ABaseCharacter::NeedDead()
{
	if (Health <= 0)
		return true;

	return false;
}

bool ABaseCharacter::CanDead()
{
	if (!NeedDead())
		return false;

	if (bDying || bDead)
		return false;

	return true;
}

void ABaseCharacter::Dead(bool bInstantDead, bool bRagdollMode /*= true*/)
{
	//Maybe Broadcast Something Later
	StartDead(bInstantDead, bRagdollMode);
}

void ABaseCharacter::StartDead(bool bInstantDead, bool bRagdollMode /*= true*/)
{
	bDying = true;

	//Essential Death Process ~
	GetTDCharacterMovement()->StopMovementImmediately();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//~ Essential Death Process

	//즉시 사망의 경우 바로 EndDead 호출
	if (bInstantDead)
	{
		EndDead();
		return;
	}

}

void ABaseCharacter::EndDead()
{
	bDead = true;
}
#pragma endregion

#pragma region Ragdoll
void ABaseCharacter::StartRagdollMode()
{

}

void ABaseCharacter::EndRagdollMode()
{

}
#pragma endregion