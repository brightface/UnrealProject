// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal.h
#include "Animation/AnimInstance.h"
#include "SH_AnimInstance.generated.h"


// for ��Ƽĳ��Ʈ ��������Ʈ ����
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);



UCLASS()
class UNREALPROJECT_API USH_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USH_AnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// for Montage
	void PlayAttackMontage();

	// ���� ��Ÿ�� �������� �Ѿ�� ���� �Լ�
	void JumpToAttackMontageSection(int32 NewSection);

public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnNextAttackCheckDelegate OnNextAttackCheck;

private:
	// ��Ƽ���� �Լ�. _������ ������ ��Ƽ���� �̸��� ��Ȯ�� ��ġ�ؾ��Ѵ�.
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	FName GetAttackMontageSectionName(int32 Section);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};
