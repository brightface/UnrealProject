// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SHGameModeBase.h"
#include "SungHoon/SHPawn.h" // added SHpawn.h
#include "SungHoon/SHPlayerController.h" // SHPlayerController.h

ASHGameModeBase::ASHGameModeBase()
{
	// pawn Ŭ���� ������ ���Ӹ�� �� Ŭ���� ������ ����.
	DefaultPawnClass = ASHPawn::StaticClass();

	// BP�� ���� ���� �ѱ���� �Ʒ�ó�� �Ѵ�.
	/*
	static ConstructorHelpers::FClassFinder<APawn>
		BP_PAWN_SH(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C"));

	if (BP_PAWN_SH.Succeeded())
	{
		// DefaultPawnClass�� BP �� Ŭ���� ������ ���.
		DefaultPawnClass = BP_PAWN_SH.Class;
	}
	*/

	// PlayerController�� ���� Ŭ���� ������ ���Ӹ��� �Ѱ�����.
	PlayerControllerClass = ASHPlayerController::StaticClass();
}

// �÷��̾ �����ϸ� ���� ����� PostLogin �̺�Ʈ �Լ��� ȣ���.
void ASHGameModeBase::PostLogin(APlayerController * NewPlayer)
{
	SH_LOG(Error, TEXT("PostLogin Begin"));
	
	// �÷��̾ ������ ���� �����ϰ�, �÷��̾� ��Ʈ�ѷ��� �ش� ���� ������
	Super::PostLogin(NewPlayer);
	
	SH_LOG(Error, TEXT("PostLogin End"));
}
