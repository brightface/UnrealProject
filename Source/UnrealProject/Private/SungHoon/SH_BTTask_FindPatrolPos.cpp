// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_BTTask_FindPatrolPos.h"
#include "SungHoon/SH_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

USH_BTTask_FindPatrolPos::USH_BTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}


EBTNodeResult::Type USH_BTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// �θ� �Լ��� �����ϰ� ��ȯ���� �޾��ش�.
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// ��Ʈ���ϰ� �ִ� ���� �����´�. �ش��ϴ� AI��Ʈ�ѷ��� �����ϰ� �ű⼭ ���� ������.
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	// AI �� ������ �������� ���ߴٸ�
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// �׺���̼� �ý����� ����κ��� �����´�.
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());

	// �׺���̼� �ý����� �������� ���Ѵٸ�
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// �׽�ũ�� �����ϴ� ���� ���� ��ġ ���Ͱ��� �����´�.
	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ASH_AIController::HomePosKey);

	FNavLocation NextPatrol;

	// �׺���̼� �ý����� ���� ������ ���� ������ �� �ִٸ� ���. NextPatrol�� �� ��ġ���� ����
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPatrol))
	{
		// �׽�ũ�� �����ϴ� ���� ������ ���� PatroPosKey ���� ���� �̵��� ��ġ������ �������ش�.
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ASH_AIController::PatrolPosKey, NextPatrol.Location);
		// ������ ��ȯ
		return EBTNodeResult::Succeeded;
	}
	
	// ������ ���� �޾ƿ��� ���ߴٸ� ����
	return EBTNodeResult::Failed;
}