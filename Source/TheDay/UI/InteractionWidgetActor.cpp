// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "InteractionWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "Widget/InteractionWidget.h"

AInteractionWidgetActor::AInteractionWidgetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	if (ensure(WidgetComponent))
	{
		//TimingPolicy�� GameTime���� �����Ǿ����.
		//protected�� �Ǿ��ְ� Setter�� ��� BP ���� �����ؾ���.
		//WidgetComponent->TimingPolicy=EWidgetTimingPolicy::GameTime;

		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetDrawSize(FVector2D::UnitVector);
	}
}

void AInteractionWidgetActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AInteractionWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (WidgetComponent)
	{
		InteractionWidget = Cast<UInteractionWidget>(WidgetComponent->GetUserWidgetObject());
		ensure(InteractionWidget);
	}
}

void AInteractionWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractionWidgetActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AInteractionWidgetActor::UpdateInteractionWidgetData(FInteractionWidgetBaseData InteractionData)
{
	if(!InteractionWidget)
		return;

	InteractionWidget->UpdateInteractionWidgetDelegate.Broadcast(InteractionData);
}

void AInteractionWidgetActor::ShowWidget()
{
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
}

void AInteractionWidgetActor::HideWidget()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}