// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

#include "BTTaskNode_TD.h"

EBTNodeResult::Type UBTTaskNode_TD::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);

}

EBTNodeResult::Type UBTTaskNode_TD::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UBTTaskNode_TD::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTaskNode_TD::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess)
{
	Super::OnMessage(OwnerComp, NodeMemory, Message, RequestID, bSuccess);
}

void UBTTaskNode_TD::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

FName UBTTaskNode_TD::GetNodeIconName() const
{
	return Super::GetNodeIconName();
}

void UBTTaskNode_TD::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}
