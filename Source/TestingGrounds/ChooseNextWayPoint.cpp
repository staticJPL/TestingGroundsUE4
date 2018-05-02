// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	// Index Key is a struct, the get value returns the index number of the data stored in the blackboard, Takes an FName String that is taken from
	// The drop down.
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto PatrolRouteComp = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRoute>();
	auto PatrolPoints = GetControlPoints(PatrolRouteComp);
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	if (!ensure(PatrolRouteComp)) { return EBTNodeResult::Failed; }
	if (PatrolPoints.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("A Guard is missing patrol points"));
		return EBTNodeResult::Failed;
	}
	SetNextWayPoint(PatrolPoints, Index, BlackBoardComp);
	CycleIndex(Index, PatrolPoints, BlackBoardComp);

	return EBTNodeResult::Succeeded;
}


TArray<AActor*> UChooseNextWayPoint::GetControlPoints(UPatrolRoute *PatrolRouteComp) {
	return PatrolRouteComp->GetPatrolPoints();
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



