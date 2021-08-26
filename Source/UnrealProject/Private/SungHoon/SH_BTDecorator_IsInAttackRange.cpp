// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_BTDecorator_IsInAttackRange.h"
#include "SungHoon/SH_AIController.h"
#include "SungHoon/SH_Character.h"
#include "BehaviorTree/BlackboardComponent.h"



USH_BTDecorator_IsInAttackRange::USH_BTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool USH_BTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// AI ���� ã��
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	// �����ϴ� ���� ��ã���� false
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	// Target�� �ִ� object���� �����ͼ� ASH_Character�� ĳ����.
	auto Target = Cast<ASH_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASH_AIController::TargetKey));
	// Ÿ���� ��ã���� false
	if (Target == nullptr)
	{
		return false;
	}

	// Ÿ��� ���� AI�� �ִܰŸ��� 200cm ���϶�� true
	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);

	return bResult;
}
