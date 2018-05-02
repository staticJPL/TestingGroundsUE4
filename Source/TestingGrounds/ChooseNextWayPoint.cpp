// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "PatrollingGuard.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto PatrolPoints = GetControlPoints(OwnerComp);
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	if (PatrolPoints.Num() == 0) {
		return EBTNodeResult::Failed;
	}
	SetNextWayPoint(PatrolPoints, Index, BlackBoardComp);
	CycleIndex(Index, PatrolPoints, BlackBoardComp);
	//Index Key is a struct, the get value returns the index number of the data stored in the blackboard, Takes an FName String that is taken from
	// The drop down.
	return EBTNodeResult::Succeeded;
}



TArray<AActor*> UChooseNextWayPoint::GetControlPoints(UBehaviorTreeComponent& OwnerComp) {
	// Need AI controller Include To GetPawn
	auto Guard = Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn());
	return Guard->GetPatrolPoints();
	
}

void UChooseNextWayPoint::SetNextWayPoint(TArray<AActor*> &PatrolPoints,int32& Index, UBlackboardComponent* BlackBoardComp) {
	auto NextWayPoint = PatrolPoints[Index];
	BlackBoardComp->SetValueAsObject(WayPoint.SelectedKeyName, NextWayPoint);
}

void UChooseNextWayPoint::CycleIndex(int32& Index, TArray<AActor*> &PatrolPoints, UBlackboardComponent* BlackBoardComp) {
	int32 ModIndex;
	Index++;
	ModIndex = Index % PatrolPoints.Num();
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, ModIndex);
}



