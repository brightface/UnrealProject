// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_AnimInstance.h"

USH_AnimInstance::USH_AnimInstance()
{
	CurrentPawnSpeed = 0.0f; // ó������ �ӵ� 0
	IsInAir = false; // ó������ ������ �����ϹǷ�.
	IsDead = false; // ó������ ��������Ƿ�.

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SH_ATTACK_MONTAGE(TEXT(
		"/Game/SungHoon/Animation/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
	if (SH_ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = SH_ATTACK_MONTAGE.Object;
	}
}

void USH_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	// ���� �� �ִ��ν��Ͻ��� ��ӹް� �ִ� ���� ������ ������.
	auto Pawn = TryGetPawnOwner();
	// ���� �������� ���ߴٸ� ����
	if (!::IsValid(Pawn)) return;
	
	// + ���� ����ִٸ�
	if(!IsDead)
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

void USH_AnimInstance::PlayAttackMontage()
{
	// �׾����� ����
	SH_CHECK(!IsDead);
	Montage_Play(AttackMontage, 1.0f);
}


void USH_AnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	// �׾����� ����
	SH_CHECK(!IsDead);
	// ���������� ������ ��ũ�� �α� ���.
	SH_CHECK(Montage_IsPlaying(AttackMontage));
	// ��Ÿ���� ���� �������� �̵��ϴ� �Լ�
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void USH_AnimInstance::AnimNotify_AttackHitCheck()
{
	SH_LOG_S(Warning);
	// ��ϵ� ��� ��������Ʈ �Լ� ȣ��. ������ ��ϵȰ� ���� ����.
	// ���߿� �浹ó���� �����Ͽ� ������ �����Ҷ� ������ ����. ������ Broadcast�ϴ� ������ ����.
	OnAttackHitCheck.Broadcast();
}

void USH_AnimInstance::AnimNotify_NextAttackCheck()
{
	SH_LOG_S(Warning);
	// ��ϵ� ��� ��������Ʈ �Լ� ȣ��
	OnNextAttackCheck.Broadcast();
}

FName USH_AnimInstance::GetAttackMontageSectionName(int32 Section)
{
	SH_CHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
