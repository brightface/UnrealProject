// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal
#include "Blueprint/UserWidget.h"
#include "SH_CharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API USH_CharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void BindCharacterStat(class USH_CharacterStatComponent* NewCharacterStat);

protected:
	// UI �ý����� �غ�Ǹ� ȣ��Ǵ� �Լ�
	virtual void NativeConstruct() override;
	// HPBar ���� ������Ʈ �Լ�
	void UpdateHPWidget();

private:
	// �������� ����. ���漱����
	TWeakObjectPtr<class USH_CharacterStatComponent> CurrentCharacterStat;

	// ProgressBar�� ���� ���漱�� �� ������ ���� ����
	UPROPERTY()
	class UProgressBar* HPProgressBar;

};
