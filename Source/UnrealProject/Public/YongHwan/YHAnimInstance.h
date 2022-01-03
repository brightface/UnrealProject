// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../UnrealProject.h"
#include "Animation/AnimInstance.h"
#include "YHAnimInstance.generated.h"

//DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
//DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UYHAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UYHAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* YH_AttackMontage;
};
