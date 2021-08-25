// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal
#include "Components/ActorComponent.h"
#include "SH_CharacterStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJECT_API USH_CharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USH_CharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// PostInitializeComponents �Լ��� ����Ǳ����� ȣ��ȴ�.
	virtual void InitializeComponent() override;

public:
	// ���� ���� �Լ�, ������ ������ �Լ�.
	void SetNewLevel(int32 NewLevel);
	// �������� �������� ó����.
	void SetDamage(float NewDamage);
	// �ش� ������ player�� ���ݷ��� ������
	float GetAttack();

	// ��������Ʈ ����
	FOnHPIsZeroDelegate OnHPIsZero;


private:
	// ����ü ���漱��
	struct FSHCharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;
	// Transient�� ����ȭ�� ���ܽ�Ű�� Ű����
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;

//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
