// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_AnimInstance.h"

USH_AnimInstance::USH_AnimInstance()
{
	CurrentPawnSpeed = 0.0f; // ó������ �ӵ� 0
	IsInAir = false; // ó������ ������ �����ϹǷ�.
}

void USH_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();

		// Character Ŭ������ GetMovementComponent�� �������� ���ؼ� ������ ĳ������ �Ѱ���.
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}

}
