// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/CommonStruct.h"
#include "InteractionWidgetActor.generated.h"

class UInteractionWidget;
class UWidgetComponent;

UCLASS()
class THEDAY_API AInteractionWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:
	AInteractionWidgetActor();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma region Interaction Widget
public:
	void UpdateInteractionWidgetData(FInteractionWidgetBaseData InteractionData);
	void ShowWidget();
	void HideWidget();
	
	FORCEINLINE UInteractionWidget* GetInteractionWidget() { return InteractionWidget; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(BlueprintReadOnly)
	class UInteractionWidget* InteractionWidget;
#pragma endregion
};
