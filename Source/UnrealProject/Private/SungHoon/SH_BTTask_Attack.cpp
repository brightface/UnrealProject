// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_BTTask_Attack.h"
#include "SungHoon/SH_AIController.h"
#include "SungHoon/SH_Character.h"


USH_BTTask_Attack::USH_BTTask_Attack()
{
	// TickTask �Լ� ȣ��ǵ��� ��. Tick Ȱ��ȭ
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type USH_BTTask_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// AI ���� ������
	auto SHCharacter = Cast<ASH_Character>(OwnerComp.GetAIOwner()->GetPawn());
	// �������� ���ߴٸ� ����
	if (SHCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// AI�� ������ ����
	SHCharacter->Attack();
	IsAttacking = true;
	// ĳ������ OnAttackEnd ��������Ʈ�� ���ε���. �ִϸ��̼��� ����Ǹ� ȣ��
	SHCharacter->OnAttackEnd.AddLambda([this]() ->void {
		IsAttacking = false;
	});

	// ���������� �˸�
	return EBTNodeResult::InProgress;
}

// Tick �Լ�
void USH_BTTask_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	// ���������� ������ ����
	if (!IsAttacking)
	{
		// Task�� �����ٴ°��� �˷��ִ� �Լ�.
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
