// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractionComponent.generated.h"

UCLASS()
class THEDAY_API UInteractionComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UInteractionComponent();

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

#pragma region Interaction
public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact();
	UFUNCTION(BlueprintCallable)
	virtual bool CanInteract();

	virtual void OnCompleteInteract();
	virtual void OnCancelInteract();
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnCompleteInteract();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnCancelInteract();
protected:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool bInteractionActive;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool bInstantInteraction;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool bInteracting;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float ElapsedInteractTime;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float MaxInteractTime;
#pragma endregion
};
#pragma endregion

#pragma region Interaction_Master
//플레이어가 사용하는 Interaction_Master Component
UCLASS()
class THEDAY_API UInteractionMasterComponent : public UInteractionComponent
{
	GENERATED_BODY()

public:
	UInteractionMasterComponent();

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Interaction
	virtual void Interact() override;
	virtual bool CanInteract() override;
#pragma endregion

};
#pragma endregion