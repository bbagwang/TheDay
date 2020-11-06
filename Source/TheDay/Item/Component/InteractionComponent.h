// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractionComponent.generated.h"

#pragma region Interaction_Base
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
    virtual bool CanInteract();

    FORCEINLINE float GetInteractionRadus() const { return InteractionRadius; }
    FORCEINLINE bool IsInteracting() const { return bInteracting; }
    FORCEINLINE bool IsInteractionActive() const { return bInteractionActive; }
    FORCEINLINE bool IsInstantInteraction() const { return bInstantInteraction; }
    FORCEINLINE float GetMaxInteractTime() const { return MaxInteractTime; }

protected:
    UFUNCTION(BlueprintCallable)
    virtual void StartInteraction();
    UFUNCTION(BlueprintImplementableEvent)
    void ReceiveStartInteraction();
    UFUNCTION(BlueprintCallable)
    virtual void EndInteraction();
    UFUNCTION(BlueprintImplementableEvent)
    void ReceiveEndInteraction();

protected:
    UFUNCTION(BlueprintImplementableEvent)
    void ReceiveOnCompleteInteract();
    UFUNCTION(BlueprintImplementableEvent)
    void ReceiveOnCancelInteract();

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
};
#pragma endregion

#pragma region Interaction_Master
//플레이어가 사용하는 Interaction_Master Component
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

private:
    UFUNCTION()
    void OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void UpdateTargetInteractor();

protected:
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
    float InteractorSearchRadius;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float ElapsedInteractTime;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
    bool bInteractionKeyPressed;
    
private:
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
    TArray<UInteractionComponent*> Interactors;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
    UInteractionComponent* TargetInteractor;
#pragma endregion
};
#pragma endregion
