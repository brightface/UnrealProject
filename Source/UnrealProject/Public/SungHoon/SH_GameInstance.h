// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal
#include "Engine/DataTable.h" // for FTableRowBase clas
#include "Engine/GameInstance.h"
#include "SH_GameInstance.generated.h"


USTRUCT(BlueprintType)
struct FSHCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSHCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};


/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USH_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	USH_GameInstance();

	// ������ ���� ����Ǹ� �ڵ����� ȣ��Ǵ� �Լ�.
	virtual void Init() override;

	// ������ �´� ��(Row)�� FSHCharacterData�� ��ȯ����. �� ����ü.
	FSHCharacterData* GetSHCharacterData(int32 Level);

private:
	// ���漱�� & ������ ���̺��� �о�� ������ ���� ����
	UPROPERTY()
	class UDataTable* SHCharacterTable;

};
