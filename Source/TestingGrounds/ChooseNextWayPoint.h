// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWayPoint.generated.h"

class APatrollingGuard;

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API UChooseNextWayPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	//Only Children See this
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector IndexKey;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WayPoint;

private:
	APatrollingGuard* PatrollingGuard = nullptr;
	TArray<AActor*> GetControlPoints(UBehaviorTreeComponent& OwnerComp);
	void SetNextWayPoint(TArray<AActor*> &PatrolPoints,int32 &Index, UBlackboardComponent* BlackBoardComp);
	void CycleIndex(int32& Index, TArray<AActor*> &PatrolPoints, UBlackboardComponent* BlackBoardComp);
};
