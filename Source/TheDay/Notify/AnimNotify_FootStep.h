// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_FootStep.generated.h"

UCLASS()
class THEDAY_API UAnimNotify_FootStep : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override { return TEXT("FootStep"); }
	FString GetEditorComment() override { return TEXT("FootStep"); }

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;
};
