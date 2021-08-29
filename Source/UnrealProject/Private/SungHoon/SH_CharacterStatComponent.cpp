// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_CharacterStatComponent.h"
#include "SungHoon/SH_GameInstance.h"

// Sets default values for this component's properties
USH_CharacterStatComponent::USH_CharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // tick�� ������.
	bWantsInitializeComponent = true; // InitializeComponent �Լ��� �Ѵ޶�.


	Level = 1;
}


// Called when the game starts
void USH_CharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void USH_CharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	// �ʱ�ȭ
	SetNewLevel(Level);
}

// ������ �Լ�
void USH_CharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	// GameInstanceŬ������ �����ö� ������Ʈ ���ÿ��� �����س��� GameInstance�� �������� �ִ�.
	// ���� ������Ʈ �������� �Ѱ� �ƴ϶��, �������� ������� �����;��ҵ�.
	// ������Ʈ ���ÿ� �س��°� ������ �̱��� ȿ����� �����. ���� ���� ���ϱ� �𸮾󿡼� �ϳ� ������ذ���.
	auto SHGameInstance = Cast<USH_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// SHGameInstance�� ����� �����Դٸ�
	SH_CHECK(SHGameInstance != nullptr);

	// Level�� �ش��ϴ� ���� row ������ ������ �� �ִ�.
	// �� row�� �޴� �ڷ����� ����ü������. �ű⿡ �Ȱ��� row�� �ڷ����� ����.
	CurrentStatData = SHGameInstance->GetSHCharacterData(NewLevel);

	if (CurrentStatData != nullptr)
	{
		// ���� ������ ���ο� ������ ���� ����
		Level = NewLevel;
		// ���� HP�� ���ο� ����(NewLevel)�� �ش��ϴ� MaxHP������ ����. Ǯ�ǵ�
		SetHP(CurrentStatData->MaxHP); // ������ ��Ȳ�̶�� �����.
	}
	else
	{
		// CurrentStatData�� ���� ����Ű�� ���� ������
		SH_LOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void USH_CharacterStatComponent::SetDamage(float NewDamage)
{
	// CurrentStatData�� �� ������ ������ ���.
	// ���� 1������ �ʱ�ȭ�Ǹ鼭 ������ ��. InitializeComponent����
	SH_CHECK(CurrentStatData != nullptr);
	// �������� ���°��� �ּ� 0 ~ �ִ� HP �� ���̷� ��������. 0 ������ ������ ���� ����.
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

void USH_CharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	// OnHPChanged�� ���ε��� ��������Ʈ �Լ��� ��� ȣ���Ѵ�. �̺�Ʈ �ߵ�!
	OnHPChanged.Broadcast();
	// ����HP�� 0�̶�� (��� �����ߴٸ�)
	// KINDA_SMALL_NUMBER : 0�� ���Ҷ� ���� ������ ������ �����Ҷ� ���. (=�ſ� ���� ���)
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		// �ſ����� ��� ���϶�� 0���� ����
		CurrentHP = 0.0f;
		// OnHPIsZero�� ���ε��� ��������Ʈ �Լ��� ��� ȣ���Ѵ�. �̺�Ʈ �ߵ�!
		OnHPIsZero.Broadcast();
	}
}

float USH_CharacterStatComponent::GetHPRatio() const
{
	// CurrentStatData�� ���������� �ִٸ� ���
	SH_CHECK(CurrentStatData != nullptr, 0.0f);
	// �ſ� ���� ��� ���϶�� 0���� ���, �װ� �ƴ϶�� ���� HP / �ִ� HP => �Ҽ������� ����. x100�ϸ� �����%��.
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}

// �ش� ������ player�� ���ݷ��� ������
float USH_CharacterStatComponent::GetAttack() const
{
	// CurrentStatData�� �� ������ ������ ���.
	// ���� 1������ �ʱ�ȭ�Ǹ鼭 ������ ��. InitializeComponent����
	SH_CHECK(CurrentStatData != nullptr, 0.0f);
	return CurrentStatData->Attack;
}

// ���� ����ġ ��ȯ
int32 USH_CharacterStatComponent::GetDropExp() const
{
	// ����ġ ��ȯ
	return CurrentStatData->DropExp;
}
