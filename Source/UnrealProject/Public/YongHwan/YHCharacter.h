// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../UnrealProject.h"
#include "GameFramework/Character.h"
#include "YHCharacter.generated.h"

UCLASS()
class UNREALPROJECT_API AYHCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYHCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	enum class EControlMode
	{
		GTA,
		DIABLO
	};

	void SetControlMode(int32 ControlMode);
	void SetControlMode(EControlMode NewControlMode);
	EControlMode CurrentControlMode;
	FVector DirectionToMove;


	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;
private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	void ViewChange();
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	void AttackStartComboState();
	void AttackEndComboState();

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadONly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadONly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadONly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadONly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadONly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UYHAnimInstance* YHAnim;
};
