// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_GameInstance.h"

USH_GameInstance::USH_GameInstance()
{
	// �̷��� ��θ� ���ڿ� ������(FString) ��� �������� ����. ���δ� ������
	FString CharacterDataPath = TEXT(
		"/Game/SungHoon/GameData/ABCharacterData.ABCharacterData");

	// ���� ���ڿ��� �̿��ؼ� �ּ��� ã�ƿ�. �̶� ���ڿ����� *�� ���������. ���� ����(��)�� ǥ���ϱ�����.
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SHCHARACTER(*CharacterDataPath);

	// ���������� �޾ƿ������� ���
	SH_CHECK(DT_SHCHARACTER.Succeeded());
	// UDataTable ������ ���.
	SHCharacterTable = DT_SHCHARACTER.Object;
	// �ߵ��Դٸ�, ���̺��� RowMap�� ������ ���ڸ� �а�, �� ���� 0���� ũ�� ���.
	SH_CHECK(SHCharacterTable->GetRowMap().Num() > 0);
}

void USH_GameInstance::Init()
{
	Super::Init();
	// SHCharacterTable�� �޾ƿ� ���� ������ ��������, 20��° �࿡ �����Ͽ� ���� �����͸� �����´�.
	SH_LOG(Error, TEXT("DropExp of Level 20 SHCharactor : %d"), GetSHCharacterData(20)->DropExp);
}

FSHCharacterData * USH_GameInstance::GetSHCharacterData(int32 Level)
{
	// int���� string���� �ٲٴ� FString::FromInt(int), �ش��ϴ� ���� row �����͸� �������� FindRow�Լ�.
	return SHCharacterTable->FindRow<FSHCharacterData>(*FString::FromInt(Level), TEXT(""));
}
