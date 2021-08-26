// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_BTService_Detect.h"
#include "SungHoon/SH_AIController.h"
#include "SungHoon/SH_Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"


USH_BTService_Detect::USH_BTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f; // 1�ʸ��� tick ����
}

void USH_BTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// ���� �����̺��Ʈ���� ����ϰ� �ִ� ���� ������
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	// ���� ������ �� ������ ����
	if (ControllingPawn == nullptr) return;

	// ���� ���� ���� ������ ������
	UWorld* World = ControllingPawn->GetWorld();
	// ���� ���� ��ġ�� ������
	FVector Center = ControllingPawn->GetActorLocation();
	// Ž���ϴ� ���� �ݰ� 600mm = 60cm
	float DetectRadius = 600.0f;

	// ���� ������ ������ �� ������ ����
	if (World == nullptr) return;

	// �ݰ泻 ��� ĳ���� ������ ���� ����
	TArray<FOverlapResult> OverlapResults;

	// �ڱ��ڽ��� �����ϴ� Ư���� �߰�
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

	// Attack�̶�� �ݸ��� ä���� ���� ��� ����� �������� �����ϴ��� ��ĵ. (������ ���� �ƴ� ���� ������ �˻�)
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults, // �浹ó�� ����� ���� ����
		Center,			// ��� �������� ��ĵ����
		FQuat::Identity,// ȸ�� ���´� ����Ʈ������.
		ECollisionChannel::ECC_GameTraceChannel2, // Attack �ݸ��� ä�� ����ϴ� �� ����
		FCollisionShape::MakeSphere(DetectRadius), // �浹 Ž���� �ݰ��� ��ü.
		CollisionQueryParam // Ư�̻��� ����
	);

	/// TODO : Ž���� ����� �÷��̾����� �Ǻ�

	// Ž���� ����� �ִٸ�
	if (bResult)
	{
		// �ϴ� TargetKey�� nullptr�� �ʱ�ȭ.
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASH_AIController::TargetKey, nullptr);

		// �浹�� ������ ������ ���鼭
		for (auto const& OverlapResult : OverlapResults)
		{
			// �ش� ���͸� ĳ����
			ASH_Character* SHCharacter = Cast<ASH_Character>(OverlapResult.GetActor());

			// SHCharacter�� ��ȿ�ϰ�, �� ĳ���Ͱ� �÷��̾� ��Ʈ�ѷ����� (�÷��̾�����)
			if (SHCharacter && SHCharacter->GetController()->IsPlayerController())
			{
				// TargetKey�� �÷��̾� ������Ʈ�� ����.
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASH_AIController::TargetKey, SHCharacter);
				// �ʷϻ� ��ü�� �׸�
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				// target ĳ���� ��ġ�� �Ķ����� ����.
				DrawDebugPoint(World, SHCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				// AI ���ؿ��� target���� ���� ����.
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), SHCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASH_AIController::TargetKey, nullptr);
		// Ž���Ȱ� ������ Ž�� ��ü �ݰ��� �׸�
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	}
}