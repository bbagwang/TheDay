// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UStaticMeshComponent;

UCLASS()
class THEDAY_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LocalizedName;

public:
	FORCEINLINE UStaticMeshComponent* GetMesh() { return ItemMesh; }
	FORCEINLINE FName GetItemName() const { return ItemName; }
	FORCEINLINE FText GetLocalizedName() const { return LocalizedName; }
};
