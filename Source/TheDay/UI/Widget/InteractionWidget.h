// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common/CommonStruct.h"
#include "InteractionWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateInteractionWidgetDelegate, FInteractionWidgetBaseData, InteractionData);

UCLASS()
class THEDAY_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInteractionWidget(const FObjectInitializer& ObjectInitializer);

protected:
	void NativeOnInitialized() override;
	void NativePreConstruct() override;
	void NativeConstruct() override;
	void NativeDestruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

#pragma region Interaction Widget
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInteractionWidgetData(FInteractionWidgetBaseData InteractionWidgetData);
	UFUNCTION(BlueprintCallable)
	void UpdateInteractionRatio(float NewRatio);
public:
	FUpdateInteractionWidgetDelegate UpdateInteractionWidgetDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractionRatio;
#pragma endregion

};
