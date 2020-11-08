// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "Item.generated.h"

class ABaseCharacter;
class USkeletalMeshComponent;
class UInteractionComponent;

UCLASS()
class THEDAY_API AItem : public AActor, public IInteractionInterface
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
	//소유자 캐릭터
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
	//아이템 메시
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* ItemMesh;
	//아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	//현지화 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LocalizedText;
#pragma endregion

#pragma region Inventory
public:
	virtual void OnTaken();
	virtual bool CanTake();
#pragma endregion

#pragma region Interaction
public:
	//Interaction Interface ~
	virtual void Interact_Implementation() override;
	virtual void OnCompleteInteraction_Implementation() override;
	virtual void OnCancelInteraction_Implementation() override;
	virtual bool CanInteract_Implementation() override;
	virtual FInteractionWidgetBaseData GetInteractionWidgetData_Implementation() override;
	//~ Interaction Interface

	UFUNCTION()
	virtual void OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FORCEINLINE UInteractionComponent* GetInteractionComponent() { return InteractionComponent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UInteractionComponent* InteractionComponent;
#pragma endregion

#pragma region Names
protected:
	static const FName ItemMeshName;
	static const FName InteractionComponentName;
#pragma endregion
};
