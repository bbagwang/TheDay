// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Common/CommonNameSpace.h"
#include "Component/WeaponManagerComponent.h"
#include "Item/Component/InteractionComponent.h"

static int32 DebugWeaponAiming = 0;
FAutoConsoleVariableRef CVARDebugAiming(TEXT("td.setaiming"), DebugWeaponAiming, TEXT("0 : NoAim 1 : Aim"), ECVF_Cheat);

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer.DoNotCreateDefaultSubobject(InteractionComponentName))
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
    InteractionMasterComponent = CreateDefaultSubobject<UInteractionMasterComponent>(TEXT("Interaction Master Component"));
    ensure(InteractionMasterComponent);
    InteractionMasterComponent->SetupAttachment(RootComponent);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(GetCameraComponent())
		DefaultFOV = GetCameraComponent()->FieldOfView;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAimFOV(DeltaTime);

	if (IsPlayerControlled() && DebugWeaponAiming)
	{
		Input_StartAiming();
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

    //Interaction
    PlayerInputComponent->BindAction(InputKeyName::INTERACTION, IE_Pressed, this, &APlayerCharacter::Input_StartInteraction);
    PlayerInputComponent->BindAction(InputKeyName::INTERACTION, IE_Released, this,  &APlayerCharacter::Input_EndInteraction);
}

void APlayerCharacter::Input_StartAiming()
{
    Super::Input_StartAiming();
}

void APlayerCharacter::Input_EndAiming()
{
    Super::Input_EndAiming();
}

#pragma region Interaction
void APlayerCharacter::Input_StartInteraction()
{
    UE_LOG(LogTemp, Warning, TEXT("Start Interaction"));

    if (InteractionMasterComponent)
        InteractionMasterComponent->OnPressInteractionKey();
}

void APlayerCharacter::Input_EndInteraction()
{
    UE_LOG(LogTemp, Warning, TEXT("End Interaction"));

    if (InteractionMasterComponent)
        InteractionMasterComponent->OnReleaseInteractionKey();
}
#pragma endregion

void APlayerCharacter::UpdateAimFOV(float DeltaTime)
{
	if (!GetCameraComponent())
		return;

	if (!GetWeaponManagerComponent())
		return;

	bool bIsAiming = GetWeaponManagerComponent()->IsAiming();

	float TargetFOV = bIsAiming ? GetWeaponManagerComponent()->GetAimFOV() : DefaultFOV;
	
	if (GetCameraComponent()->FieldOfView == TargetFOV)
		return;

	float InterpSpeed = GetWeaponManagerComponent()->GetAimInterpSpeed();
	float CurrentFOV = FMath::FInterpTo(GetCameraComponent()->FieldOfView, TargetFOV, DeltaTime, InterpSpeed);

	GetCameraComponent()->SetFieldOfView(CurrentFOV);
}