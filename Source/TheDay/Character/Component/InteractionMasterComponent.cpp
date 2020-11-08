// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "InteractionMasterComponent.h"
#include "Item/Component/InteractionComponent.h"
#include "Common/CommonNameSpace.h"
#include "Interface/InteractionInterface.h"
#include "DrawDebugHelpers.h"
#include "UI/InteractionWidgetActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Widget/InteractionWidget.h"

static int32 DebugInteractionSearch = 0;
FAutoConsoleVariableRef CVARDebugInteractionSearch(TEXT("td.debugInteractionSearch"), DebugInteractionSearch, TEXT("Draw Debug Interaction Search"), ECVF_Cheat);

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

	if (InteractionWidgetActorBlueprintClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetOwner() ? GetOwner()->GetInstigator() : nullptr;

		InteractionWidgetActor = GetWorld()->SpawnActor<AInteractionWidgetActor>(InteractionWidgetActorBlueprintClass, SpawnParams);
		ensure(InteractionWidgetActor);
	}
}

void UInteractionMasterComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateTargetInteractor();
	UpdateInteractionWidgetLocation();
	UpdateInteractionWidgetRatio();

	if (!TargetInteractor || TargetInteractor->IsPendingKill())
		return;

	if (!bInteractionKeyPressed)
	{
		if (ElapsedInteractTime > 0.f)
		{
			TargetInteractor->CancelInteract();
			ElapsedInteractTime = 0.f;
		}
		return;
	}

	if (!TargetInteractor->IsInteractionActive() || TargetInteractor->IsInteracting())
		return;

	//즉시 인터렉션 되는 경우 바로 Interact 실행
	if (TargetInteractor->IsInstantInteraction())
	{
		TargetInteractor->Interact();
		ElapsedInteractTime = 0.f;
	}
	else
	{
		ElapsedInteractTime += DeltaTime;
		//Max Time 만큼 누른 경우 Interact 실행
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
	UE_LOG(LogTemp, Warning, TEXT("Interaction Key Pressed!"));
}

void UInteractionMasterComponent::OnReleaseInteractionKey()
{
	bInteractionKeyPressed = false;
	ElapsedInteractTime = 0.f;
	UE_LOG(LogTemp, Warning, TEXT("Interaction Key Released!"));
}

float UInteractionMasterComponent::GetInteractionRatio() const
{
	if (TargetInteractor)
	{
		return UKismetMathLibrary::FClamp(ElapsedInteractTime / TargetInteractor->GetMaxInteractTime(), 0.f, 1.f);
	}

	return -1.f;
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
		if (!IterOwner || IterOwner == GetOwner())
			return;

		if (!IterOwner->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			return;

		bool bBlcoked = World->LineTraceSingleByChannel(HitResult, MasterLocation, Iter->GetComponentLocation(), ECC_Visibility);

		if (DebugInteractionSearch > 0)
		{
			DrawDebugLine(World, MasterLocation, Iter->GetComponentLocation(), FColor::Red, false, 0.f, 0, 0.f);
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
	if (NearestInteractor != TargetInteractor)
	{
		TargetInteractor = NearestInteractor;
		UpdateInteractionWidgetData();
	}
}

#pragma region Interaction Widget
void UInteractionMasterComponent::UpdateInteractionWidgetLocation()
{
	if (!InteractionWidgetActor)
		return;

	if (!TargetInteractor)
	{
		InteractionWidgetActor->HideWidget();
		return;
	}

	AActor* InteractorOwner = TargetInteractor->GetOwner();

	FVector WidgetLocation = InteractorOwner ? InteractorOwner->GetActorLocation() : TargetInteractor->GetComponentLocation();

	InteractionWidgetActor->SetActorLocation(WidgetLocation);
	InteractionWidgetActor->ShowWidget();
}

void UInteractionMasterComponent::UpdateInteractionWidgetData()
{
	if (!TargetInteractor || !InteractionWidgetActor)
		return;

	AActor* InteractorOwner = TargetInteractor->GetOwner();

	if (!InteractorOwner)
		return;

	if (!InteractorOwner->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		return;

	InteractionWidgetActor->UpdateInteractionWidgetData(IInteractionInterface::Execute_GetInteractionWidgetData(InteractorOwner));
}

void UInteractionMasterComponent::UpdateInteractionWidgetRatio()
{
	if (!InteractionWidgetActor)
		return;

	UInteractionWidget* InteractionWidget = InteractionWidgetActor->GetInteractionWidget();

	if (!InteractionWidget)
		return;

	InteractionWidget->UpdateInteractionRatio(GetInteractionRatio());
}

#pragma endregion