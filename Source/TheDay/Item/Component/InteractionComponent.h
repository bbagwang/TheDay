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
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Interaction
public:
    UFUNCTION(BlueprintCallable)
    virtual void Interact();
    UFUNCTION(BlueprintCallable)
    virtual void CancelInteract();
    UFUNCTION(BlueprintCallable)
    virtual bool CanInteract();

    FORCEINLINE float GetInteractionRadus() const { return InteractionRadius; }
    FORCEINLINE bool IsInteracting() const { return bInteracting; }
    FORCEINLINE bool IsInteractionActive() const { return bInteractionActive; }
    FORCEINLINE bool IsInstantInteraction() const { return bInstantInteraction; }
    FORCEINLINE float GetMaxInteractTime() const { return MaxInteractTime; }
    
protected:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
    float InteractionRadius;
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
    bool bInteracting;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bInteractionActive;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bInstantInteraction;
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float MaxInteractTime;

private:
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
    bool bOneTimeInteractor;
#pragma endregion

#pragma region Interaction Widget
public:
	FORCEINLINE FVector GetInteractionWidgetOffsetOverride() const { return WidgetOffsetOverride; }
	FORCEINLINE void SetInteractionWidgetOffsetOverride(FVector NewOffset) { WidgetOffsetOverride = NewOffset; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector WidgetOffsetOverride;
#pragma endregion
};
