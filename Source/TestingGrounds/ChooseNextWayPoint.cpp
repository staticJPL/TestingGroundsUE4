// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);


	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	//Index Key is a struct, the get value returns the index number of the data stored in the blackboard, Takes an FName String that is taken from
	// The drop down.
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	UE_LOG(LogTemp, Warning, TEXT("Waypoint index:%i"),Index);
	return EBTNodeResult::Succeeded;
}



