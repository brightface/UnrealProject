// Fill out your copyright notice in the Description page of Project Settings.


#include "YongHwan/YHAnimInstance.h"

UYHAnimInstance::UYHAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> YH_ATTACK_MONTAGE(TEXT(
		"/Game/YongHwan/Animation/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
	if (YH_ATTACK_MONTAGE.Succeeded())
	{
		YH_AttackMontage = YH_ATTACK_MONTAGE.Object;
	}
}

void UYHAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	// 현재 이 애님인스턴스를 상속받고 있는 폰의 정보를 가져옴.
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}


}
void UYHAnimInstance::PlayAttackMontage()
{
	
	/*if (!Montage_IsPlaying(YH_AttackMontage))
	{*/
		Montage_Play(YH_AttackMontage, 1.0f);
	//}
	
}
void UYHAnimInstance::AnimNotify_AttackHitCheck()
{
	YHLOG_S(Error);
}