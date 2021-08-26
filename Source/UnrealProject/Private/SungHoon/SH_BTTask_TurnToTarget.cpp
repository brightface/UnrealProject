// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_BTTask_TurnToTarget.h"
#include "SungHoon/SH_AIController.h"
#include "SungHoon/SH_Character.h"
#include "BehaviorTree/BlackboardComponent.h"



USH_BTTask_TurnToTarget::USH_BTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}


EBTNodeResult::Type USH_BTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// �����ϰ� �ִ� AI�� ���� ������
	auto SHCharacter = Cast<ASH_Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (SHCharacter == nullptr)
	{
		EBTNodeResult::Failed;
	}

	// �������� Target�� ���ִ� Object �����͸� �����ͼ� ĳ����
	auto Target = Cast<ASH_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASH_AIController::TargetKey));
	if (Target == nullptr)
	{
		EBTNodeResult::Failed;
	}

	// ���⺤�� ���ϱ�. ���𿡼� Target���� �ٶ�. AI�� Target�� �ٶ󺸴� ���⺤����.
	FVector LookVector = Target->GetActorLocation() - SHCharacter->GetActorLocation();
	
	LookVector.Z = 0.0f; // Z�� 0���� �ʱ�ȭ
	// �ٶ󺸴� ���⺤�������� �չ��� ȸ������� ����
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	// ȸ���� ����
	SHCharacter->SetActorRotation(FMath::RInterpTo(SHCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
	
	return EBTNodeResult::Succeeded;
}