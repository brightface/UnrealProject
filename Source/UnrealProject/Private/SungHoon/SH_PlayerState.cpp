// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_PlayerState.h"
#include "SungHoon/SH_GameInstance.h" // for FSH_CharacterData


ASH_PlayerState::ASH_PlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	Exp = 0;
}

int32 ASH_PlayerState::GetGameScore() const
{
	return GameScore;
}

int32 ASH_PlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

void ASH_PlayerState::InitPlayerData()
{
	// �÷��̾��� ���� ����
	SetPlayerName(TEXT("SungHoon"));
	SetCharacterLevel(5);
	GameScore = 0;
	Exp = 0;
}

// ���� ����ġ ���� ��ȯ
float ASH_PlayerState::GetExpRatio() const
{
	// ���� ����ġ ������ �ſ� ���� ���̸�
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}

	// ������ �Ϸ�ƴ��� �Ҽ���
	float Result = (float)Exp / (float)CurrentStatData->NextExp;
	// �α� ���
	SH_LOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);
	
	return Result;
}

// ����ġ �߰�
bool ASH_PlayerState::AddExp(int32 IncomeExp)
{
	// ���� ����ġ ���� -1�̸� ���� (�����̶� �ǹ�. ����ġ ������)
	if(CurrentStatData->NextExp==-1)
		return false;

	// ������ ����
	bool DidLevelUp = false;
	// �߰� ����ġ ���
	Exp = Exp + IncomeExp;

	// �߰��� ���� ����ġ�� �ʿ����ġ���� �Ѿ��ٸ� ������!
	if (Exp >= CurrentStatData->NextExp)
	{
		// ����ġ �缳��
		Exp -= CurrentStatData->NextExp;
		// ������
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}

	// �÷��̾��� ���°� �ٲ�. �缳���� ���� �Լ� ȣ��
	OnPlayerStateChanged.Broadcast();
	return DidLevelUp;
}


// GameScore �߰�
void ASH_PlayerState::AddScore()
{
	GameScore++;
	OnPlayerStateChanged.Broadcast();
}

// ĳ���� ���� �缳��
void ASH_PlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	// ���� �ν��Ͻ��� ������
	auto SHGameInstance = Cast<USH_GameInstance>(GetGameInstance());
	SH_CHECK(SHGameInstance != nullptr);

	// �ش� ������ �´� �׼������͸� ����ü ������ �̾Ƽ� ������
	CurrentStatData = SHGameInstance->GetSHCharacterData(NewCharacterLevel);
	SH_CHECK(CurrentStatData != nullptr);

	// ���� ĳ���� ���� ����
	CharacterLevel = NewCharacterLevel;
}
