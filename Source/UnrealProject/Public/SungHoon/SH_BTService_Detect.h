// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal
#include "BehaviorTree/BTService.h"
#include "SH_BTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USH_BTService_Detect : public UBTService
{
	GENERATED_BODY()
	

public:
	USH_BTService_Detect();

protected:
	// �ڽ��� ���� ������ ��尡 Ȱ��ȭ �� ���, interval �������� ����ؼ� �ڵ����� ȣ��Ǵ� tick �Լ�.
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
