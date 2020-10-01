// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "InteractionComponent.h"

UInteractionComponent::UInteractionComponent()
{

}

void UInteractionComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bInteracting)
	{
		OnCancelInteract();
		return;
	}

	ElapsedInteractTime += DeltaTime;

	if (ElapsedInteractTime >= MaxInteractTime)
	{
		OnCompleteInteract();
	}
}

#pragma region Interaction
void UInteractionComponent::Interact()
{
	if(!CanInteract())
		return;

	bInteracting = true;

	if (bInstantInteraction)
	{
		OnCompleteInteract();
		return;
	}

	SetComponentTickEnabled(true);
}

bool UInteractionComponent::CanInteract()
{
	if(bInteractionActive)
		return false;

	return true;
}

void UInteractionComponent::OnCompleteInteract()
{
	bInteractionActive = false;
	bInteracting = false;
	SetComponentTickEnabled(false);
	ReceiveOnCompleteInteract();
}

void UInteractionComponent::OnCancelInteract()
{
	bInteracting = false;
	SetComponentTickEnabled(false);
	ReceiveOnCancelInteract();
}
#pragma endregion

#pragma region Interaction_Master
UInteractionMasterComponent::UInteractionMasterComponent()
{

}

void UInteractionMasterComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UInteractionMasterComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionMasterComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UInteractionMasterComponent::Interact()
{
}
bool UInteractionMasterComponent::CanInteract()
{
	return false;
}
#pragma endregion