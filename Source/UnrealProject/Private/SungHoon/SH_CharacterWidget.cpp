// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_CharacterWidget.h"
#include "SungHoon/SH_CharacterStatComponent.h"
#include "Components/ProgressBar.h"




void USH_CharacterWidget::BindCharacterStat(class USH_CharacterStatComponent* NewCharacterStat)
{
	// NewCharacterStat�� nullptr �ƴϸ� ���
	SH_CHECK(NewCharacterStat != nullptr);

	// Character Ŭ�����κ��� CharacterStat ������ �޾ƿ�.
	CurrentCharacterStat = NewCharacterStat;
	
	// ��������Ʈ �Լ� ���. ��������Ʈ ����δ� SH_CharacterStatComponent�� ����. ����� �ܺ�.
	NewCharacterStat->OnHPChanged.AddUObject(this, &USH_CharacterWidget::UpdateHPWidget);
}

void USH_CharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ������ �̸��� ���� ������. ĳ����
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	// HPProgressBar ���� ��ȿ�ϴٸ�
	SH_CHECK(HPProgressBar != nullptr);

	UpdateHPWidget();
}

void USH_CharacterWidget::UpdateHPWidget()
{
	// CurrentCharacterStat ��ȿ�ϴٸ�
	// NativeConstruct ȣ��Ǳ����� BindCharacterStat�� ȣ��
	// BindCharacterStat�� Character�� BeginPlay���� ȣ���.
	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgressBar != nullptr)
		{
			// ���� HP ������ �Ҽ��� float�� �޾ƿͼ� PRogressBar�� ����
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
