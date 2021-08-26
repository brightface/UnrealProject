// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal
#include "AIController.h"
#include "SH_AIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API ASH_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ASH_AIController();
	// �𸮾� 4.22���� Possess -> OnPossess�� ��Ī �ٲ�
	virtual void OnPossess(APawn* InPawn) override;

	// �����忡�� ����� Ű������ ���������� �����غ���.
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	// ������
	UPROPERTY()
	class UBlackboardData* BBAsset;
	// �����̺�� Ʈ��
	UPROPERTY()
	class UBehaviorTree* BTAsset;

};
