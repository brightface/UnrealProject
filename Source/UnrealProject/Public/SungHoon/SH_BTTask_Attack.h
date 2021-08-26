// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal
#include "BehaviorTree/BTTaskNode.h"
#include "SH_BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USH_BTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	USH_BTTask_Attack();
	// ��尡 ����ɶ� ����Ǵ� �Լ�.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// ����� Tick �Լ�
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


private:
	// AI�� ������������ �Ǻ��ϴ� ����
	bool IsAttacking;
};
