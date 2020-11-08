// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "InteractionWidget.h"
#include "Character/Component/InteractionMasterComponent.h"

UInteractionWidget::UInteractionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InteractionRatio = 0.f;
}

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInteractionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateInteractionWidgetDelegate.AddDynamic(this, &UInteractionWidget::UpdateInteractionWidgetData);
}

void UInteractionWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInteractionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInteractionWidget::UpdateInteractionRatio(float NewRatio)
{
	InteractionRatio = NewRatio;
}

#pragma region Interaction Widget

#pragma endregion