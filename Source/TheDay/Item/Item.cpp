// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "Item.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/InteractionComponent.h"

const FName AItem::ItemMeshName = TEXT("Item Mesh");
const FName AItem::InteractionComponentName = TEXT("Interaction");

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(AItem::ItemMeshName);
	ensure(ItemMesh);
	SetRootComponent(ItemMesh);
	ItemMesh->SetRenderStatic(true);

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(AItem::InteractionComponentName);
	ensure(InteractionComponent);
	InteractionComponent->SetupAttachment(ItemMesh);
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	LoadItemDataFromDataTable();

	if(!InteractionComponent->OnComponentBeginOverlap.IsBound())
		InteractionComponent->OnComponentBeginOverlap.AddDynamic(this,&AItem::OnInteractionBeginOverlap);
	if (!InteractionComponent->OnComponentEndOverlap.IsBound())
		InteractionComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnInteractionEndOverlap);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (InteractionComponent->OnComponentBeginOverlap.IsAlreadyBound(this, &AItem::OnInteractionBeginOverlap))
		InteractionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AItem::OnInteractionBeginOverlap);
	if (InteractionComponent->OnComponentEndOverlap.IsAlreadyBound(this, &AItem::OnInteractionEndOverlap))
		InteractionComponent->OnComponentEndOverlap.RemoveDynamic(this, &AItem::OnInteractionEndOverlap);
}

#pragma region Item
void AItem::LoadItemDataFromDataTable()
{

}
#pragma endregion

#pragma region Inventory
void AItem::OnTaken()
{

}

bool AItem::CanTake()
{
	return true;
}
#pragma endregion

#pragma region Interaction
// void AItem::Interact()
// {
// 	UE_LOG(LogTemp, Warning, TEXT("Interact"));
// }

void AItem::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact Impl"));
}

// void AItem::OnCompleteInteraction()
// {
// 	UE_LOG(LogTemp, Warning, TEXT("Completed"));
// }

void AItem::OnCompleteInteraction_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Completed Impl"));
}

// void AItem::OnCancelInteraction()
// {
// 	UE_LOG(LogTemp, Warning, TEXT("Cancel"));
// }

void AItem::OnCancelInteraction_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Cancel Impl"));
}

// void AItem::CanInteract()
// {
// 	UE_LOG(LogTemp, Warning, TEXT("Can Interact"));
// }

bool AItem::CanInteract_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Can Interact Impl"));
	return true;
}

void AItem::OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Interactor Begin Overlap"));
}

void AItem::OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Interactor End Overlap"));
}
#pragma endregion