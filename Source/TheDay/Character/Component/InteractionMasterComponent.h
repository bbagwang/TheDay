// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractionMasterComponent.generated.h"

class UInteractionComponent;
class AInteractionWidgetActor;

UCLASS()
class THEDAY_API UInteractionMasterComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UInteractionMasterComponent();

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma region Interaction
public:
	void OnPressInteractionKey();
	void OnReleaseInteractionKey();

	UFUNCTION(BlueprintPure)
	float GetInteractionRatio() const;

private:
	UFUNCTION()
	void OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdateTargetInteractor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float InteractorSearchRadius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ElapsedInteractTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bInteractionKeyPressed;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UInteractionComponent*> Interactors;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInteractionComponent* TargetInteractor;
#pragma endregion

#pragma region Interaction Widget
protected:
	void UpdateInteractionWidgetLocation();
	void UpdateInteractionWidgetData();
	void UpdateInteractionWidgetRatio();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AInteractionWidgetActor> InteractionWidgetActorBlueprintClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AInteractionWidgetActor* InteractionWidgetActor;
#pragma endregion
};