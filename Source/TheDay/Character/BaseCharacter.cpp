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

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("Status Component"));
	ensure(StatusComponent);
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	ensure(InventoryComponent);
	WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponent>(TEXT("Weapon Manager Component"));
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
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ABaseCharacter::StartAiming);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ABaseCharacter::EndAiming);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABaseCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ABaseCharacter::EndCrouch);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABaseCharacter::StartAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ABaseCharacter::EndAttack);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ABaseCharacter::StartInteraction);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &ABaseCharacter::EndInteraction);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABaseCharacter::LookUpAtRate);
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

void ABaseCharacter::StartAiming()
{
	if (!GetWeaponManagerComponent())
		return;

	GetWeaponManagerComponent()->SetAiming(true);
}

void ABaseCharacter::EndAiming()
{
	if (!GetWeaponManagerComponent())
		return;

	GetWeaponManagerComponent()->SetAiming(false);
}
#pragma endregion

#pragma region Crouch
void ABaseCharacter::StartCrouch()
{
	Crouch();
}

void ABaseCharacter::EndCrouch()
{
	UnCrouch();
}
#pragma endregion

#pragma region Attack
void ABaseCharacter::StartAttack()
{
	if (!WeaponManagerComponent)
		return;
	WeaponManagerComponent->bAttackKeyPressed = true;
	WeaponManagerComponent->Attack();
}

void ABaseCharacter::EndAttack()
{
	if (!WeaponManagerComponent)
		return;

	WeaponManagerComponent->bAttackKeyPressed = false;
}
#pragma endregion

#pragma region Interaction
void ABaseCharacter::StartInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Interaction"));

}

void ABaseCharacter::EndInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("End Interaction"));

}
#pragma endregion

#pragma region Dead
void ABaseCharacter::Dead(bool bForced)
{
	if (bDead)
		return;
	
	if (!bForced)
	{
		if (GetStatusComponent())
		{
			if (GetStatusComponent()->GetHealth() >= 0.f)
				return;
		}
	}

	StartDead();
}

void ABaseCharacter::StartDead()
{
	GetTDCharacterMovement()->StopMovementImmediately();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Anim Processing
}

void ABaseCharacter::EndDead()
{
	bDead = true;
}
#pragma endregion