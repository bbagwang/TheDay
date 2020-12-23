// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class ABaseCharacter;
class USkeletalMeshComponent;
class UInteractionComponent;

UCLASS()
class THEDAY_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma region Essential
public: 
	FORCEINLINE void SetOwnerCharacter(ABaseCharacter* NewOwnerCharacter) { OwnerCharacter = NewOwnerCharacter; }
	FORCEINLINE ABaseCharacter* GetOwnerCharacter() { return OwnerCharacter; }

protected:
	//������ ĳ����
	UPROPERTY()
	ABaseCharacter* OwnerCharacter;
#pragma endregion

#pragma region Item
public:
	FORCEINLINE USkeletalMeshComponent* GetItemMesh() { return ItemMesh; }
	FORCEINLINE FName GetItemName() const { return ItemName; }
	FORCEINLINE FText GetLocalizedText() const { return LocalizedText; }

protected:
	virtual void LoadItemDataFromDataTable();

protected:
	//������ �޽�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* ItemMesh;
	//������ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	//����ȭ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LocalizedText;
#pragma endregion

#pragma region Inventory
public:
	virtual void OnTaken();
	virtual bool CanTake();
#pragma endregion

#pragma region Names
protected:
	static const FName ItemMeshName;
	static const FName InteractionComponentName;
#pragma endregion
};
