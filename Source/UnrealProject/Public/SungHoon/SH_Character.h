// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal.h
#include "GameFramework/Character.h"
#include "SH_Character.generated.h"


UENUM()
enum class EControlMode
{
	GTA,
	DIABLO
};

UCLASS()
class UNREALPROJECT_API ASH_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASH_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// View �۵���� �����Լ�. GTA vs DIABLO
	void SetControlMode(const EControlMode& NewControlMode);

	// �ʱ� ��Ʈ�� ��尪 ����
	UPROPERTY(VisibleAnywhere, Category = DEBUGING)
	EControlMode CurrentControlMode = EControlMode::GTA;
	// �����̴� ������ ���⺤��
	FVector DirectionToMove = FVector::ZeroVector;

	// SpringArm values
	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ĳ���� Ŭ���������� SpringArm, Camera component�� ���� ���������Ѵ�.
	UPROPERTY(VisibleAnywhere, Category = CAMERA)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = CAMERA)
	UCameraComponent* Camera;

private:
	// for movement
	void UpDown(const float NewAxisValue);
	void LeftRight(const float NewAxisValue);

	// for rotation
	void LookUp(const float NewAxisValue);
	void Turn(const float NewAxisValue);

	// for View control mode
	void ViewChange();

};
