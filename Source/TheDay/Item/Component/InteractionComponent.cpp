// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "InteractionComponent.h"
#include "Common/CommonNameSpace.h"
#include "Interface/InteractionInterface.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	bInteractionActive = true;
	bInstantInteraction = false;
	bInteracting = false;
	MaxInteractTime = 1.f;
	InteractionRadius = 500.f;
	InitSphereRadius(InteractionRadius);
	SetCollisionProfileName(CollisionProfileName::INTERACTION);
}

void UInteractionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetCollisionProfileName(CollisionProfileName::INTERACTION);
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

#pragma region Interaction
void UInteractionComponent::Interact()
{
	if (!CanInteract())
		return;

	AActor* InteractorOwner = GetOwner();
	if (InteractorOwner && InteractorOwner->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		if (IInteractionInterface::Execute_CanInteract(InteractorOwner))
		{
			bInteracting = true;
			bInteractionActive = false;
			SetComponentTickEnabled(true);

			IInteractionInterface::Execute_Interact(InteractorOwner);
		}
	}
}

void UInteractionComponent::CancelInteract()
{
	AActor* InteractorOwner = GetOwner();
	if (InteractorOwner && InteractorOwner->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		IInteractionInterface::Execute_OnCancelInteraction(InteractorOwner);

		bInteracting = false;
		bInteractionActive = true;
		SetComponentTickEnabled(false);
	}
}

bool UInteractionComponent::CanInteract()
{
	if (!bInteractionActive)
		return false;
	if (bInteracting)
		return false;

	return true;
}
#pragma endregion