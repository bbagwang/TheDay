// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AnimToRagdoll.generated.h"

UCLASS()
class THEDAY_API UAnimNotifyState_AnimToRagdoll : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override { return TEXT("AnimToRagdoll"); }
	FString GetEditorComment() override { return TEXT("AnimToRagdoll"); }

#pragma region Que
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
#pragma endregion

#pragma region BranchingPoint
	void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;

	void BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime) override;

	void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;
#pragma endregion
};
