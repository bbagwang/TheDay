// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "Item.h"
#include "Components/SkeletalMeshComponent.h"

const FName AItem::ItemMeshName = TEXT("Item Mesh");

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(AItem::ItemMeshName);
	ensure(ItemMesh);
	SetRootComponent(ItemMesh);
	ItemMesh->SetRenderStatic(true);

}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	LoadItemDataFromDataTable();
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