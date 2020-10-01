// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "AnimNotify_FootStep.h"

void UAnimNotify_FootStep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
}

void UAnimNotify_FootStep::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotify(BranchingPointPayload);
}