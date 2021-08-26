// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


// �������� �ʱ�ȭ
const FName ASH_AIController::HomePosKey(TEXT("HomePos"));
const FName ASH_AIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ASH_AIController::TargetKey(TEXT("Target"));


ASH_AIController::ASH_AIController()
{
	// ������ ����
	static ConstructorHelpers::FObjectFinder<UBlackboardData> SH_BBObject(TEXT(
		"/Game/SungHoon/AI/BB_SHCharacter.BB_SHCharacter"
	));
	if (SH_BBObject.Succeeded())
	{
		BBAsset = SH_BBObject.Object;
	}

	// �����̺�� Ʈ�� ����
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> SH_BTObject(TEXT(
		"/Game/SungHoon/AI/BT_SHCharacter.BT_SHCharacter"
	));
	if (SH_BTObject.Succeeded())
	{
		BTAsset = SH_BTObject.Object;
	}
}

void ASH_AIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	SH_LOG_S(Error);

	// ������ ��밡���ϴٸ� ����.
	if (UseBlackboard(BBAsset, Blackboard))
	{
		// �������� HomePosKey ���� ���� ���� ��ġ�� �����϶�. (������ġ)
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		// ���� �����̺�� Ʈ���� �۵��� �� ���ٸ�
		if (!RunBehaviorTree(BTAsset))
		{
			// �α� ���
			SH_LOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
		else
		{
			SH_LOG(Error, TEXT("RunBehaviorTree!"))
		}
	}
}

