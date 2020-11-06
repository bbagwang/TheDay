// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "InteractionComponent.h"
#include "Common/CommonNameSpace.h"
#include "Interface/InteractionInterface.h"
#include "Kismet/KismetSystemLibrary.h"

static int32 DebugInteractionSearch = 0;
FAutoConsoleVariableRef CVARDebugInteractionSearch(TEXT("td.debugInteractionSearch"), DebugInteractionSearch, TEXT("Draw Debug Interaction Search"), ECVF_Cheat);

UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = false;

    bInteractionActive = true;
    bInstantInteraction = false;
    bInteracting = false;
    MaxInteractTime = 1.f;
    InteractionRadius = 500.f;
    InitSphereRadius(InteractionRadius);
    SetCollisionProfileName(CollisionProfileName::INTERACTION);
}

void UInteractionComponent::InitializeComponent()
{
    Super::InitializeComponent();
    SetCollisionProfileName(CollisionProfileName::INTERACTION);
}

void UInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

#pragma region Interaction
void UInteractionComponent::Interact()
{
    if (!CanInteract())
        return;

    AActor* InteractorOwner = GetOwner();
    if(InteractorOwner&&InteractorOwner->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
    {
        if(IInteractionInterface::Execute_CanInteract(InteractorOwner))
        {
            IInteractionInterface::Execute_Interact(InteractorOwner);
        }
    }
}

bool UInteractionComponent::CanInteract()
{
    if (!bInteractionActive)
        return false;
    if (bInteracting)
        return false;

    return true;
}

void UInteractionComponent::StartInteraction()
{
    bInteracting = true;
    bInteractionActive = false;
    SetComponentTickEnabled(true);

    ReceiveStartInteraction();
}

void UInteractionComponent::EndInteraction()
{
    bInteracting = false;
    bInteractionActive = !bOneTimeInteractor;
    SetComponentTickEnabled(false);
    
    ReceiveEndInteraction();
}
#pragma endregion

#pragma region Interaction_Master
UInteractionMasterComponent::UInteractionMasterComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;

    InitSphereRadius(InteractorSearchRadius);
    ElapsedInteractTime = 0.f;
    bInteractionKeyPressed = false;
    SetCollisionProfileName(CollisionProfileName::INTERACTION);
}

void UInteractionMasterComponent::InitializeComponent()
{
    Super::InitializeComponent();

    SetCollisionProfileName(CollisionProfileName::INTERACTION);
}

void UInteractionMasterComponent::BeginPlay()
{
    Super::BeginPlay();

    OnComponentBeginOverlap.AddDynamic(this, &UInteractionMasterComponent::OnInteractionBeginOverlap);
    OnComponentEndOverlap.AddDynamic(this, &UInteractionMasterComponent::OnInteractionEndOverlap);
}

void UInteractionMasterComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateTargetInteractor();

    if (!TargetInteractor || TargetInteractor->IsPendingKill())
        return;

    if (!bInteractionKeyPressed)
        return;

    if (!TargetInteractor->IsInteractionActive() || TargetInteractor->IsInteracting())
        return;

    if (TargetInteractor->IsInstantInteraction())
    {
        TargetInteractor->Interact();
        ElapsedInteractTime = 0.f;
    }
    else
    {
        ElapsedInteractTime += DeltaTime;

        if (ElapsedInteractTime >= TargetInteractor->GetMaxInteractTime())
        {
            TargetInteractor->Interact();
            ElapsedInteractTime = 0.f;
        }
    }
}

void UInteractionMasterComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (OnComponentBeginOverlap.IsAlreadyBound(this, &UInteractionMasterComponent::OnInteractionBeginOverlap))
        OnComponentBeginOverlap.Clear();
    if (OnComponentEndOverlap.IsAlreadyBound(this, &UInteractionMasterComponent::OnInteractionEndOverlap))
        OnComponentEndOverlap.Clear();
}

void UInteractionMasterComponent::OnPressInteractionKey()
{
    bInteractionKeyPressed = true;
    UE_LOG(LogTemp,Warning,TEXT("Interaction Key Pressed!"));
}

void UInteractionMasterComponent::OnReleaseInteractionKey()
{
    bInteractionKeyPressed = false;
    ElapsedInteractTime = 0.f;
    UE_LOG(LogTemp,Warning,TEXT("Interaction Key Released!"));
}

void UInteractionMasterComponent::OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UInteractionComponent* OverlappedInteractor = Cast<UInteractionComponent>(OtherComp);
    if (!OverlappedInteractor)
        return;

    Interactors.Add(OverlappedInteractor);
}

void UInteractionMasterComponent::OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    UInteractionComponent* OverlappedInteractor = Cast<UInteractionComponent>(OtherComp);
    if (!OverlappedInteractor)
        return;

    Interactors.Remove(OverlappedInteractor);
}

void UInteractionMasterComponent::UpdateTargetInteractor()
{
    if (Interactors.Num() == 0)
    {
        TargetInteractor = nullptr;
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
        return;

    //Blocking Check

    static FHitResult HitResult;
    static FCollisionQueryParams CollQuery(TEXT("Interaction Master Trace"), false, GetOwner());
    FVector MasterLocation = GetComponentLocation();

    static UInteractionComponent* NearestInteractor = nullptr;
    static float NearestDistance = FLT_MAX;

    for (UInteractionComponent* Iter : Interactors)
    {
        if (!Iter)
            return;

        AActor* IterOwner = Iter->GetOwner();
        if(!IterOwner||IterOwner==GetOwner())
            return;

        //PROBLEM!
        // if(IterOwner->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
        //     return;
        
        bool bBlcoked = World->LineTraceSingleByChannel(HitResult, MasterLocation, Iter->GetComponentLocation(), ECC_Visibility);

        if (DebugInteractionSearch > 0)
        {
            // #if ENABLE_DRAW_DEBUG
            // 			DrawDebugLineTraceSingle(World, Start, End, DrawDebugType, bHit, OutHit, TraceColor, TraceHitColor, DrawTime);
            // #endif
        }
        float BlockToCompDistance = FVector::Distance(HitResult.bBlockingHit ? HitResult.ImpactPoint : HitResult.TraceEnd, Iter->GetComponentLocation());
        if (bBlcoked && BlockToCompDistance > 10.f)
            continue;

        //Distance Check

        float Distance = HitResult.Distance;

        if (Distance < NearestDistance)
        {
            NearestInteractor = Iter;
        }
    }

    TargetInteractor = NearestInteractor;
}
#pragma endregion
