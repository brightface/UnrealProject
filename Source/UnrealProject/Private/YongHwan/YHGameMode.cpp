// Fill out your copyright notice in the Description page of Project Settings.


#include "YongHwan/YHGameMode.h"
//#include "YongHwan/YHPawn.h"
#include "YongHwan/YHCharacter.h"
#include "Yonghwan/YHPlayerController.h"
//���Ӹ�� �����ڿ��� �÷��̾�����ѷ� �Ӽ��� yh�÷��̾� ��Ʈ�ѷ� Ŭ���������� ����

AYHGameMode::AYHGameMode()
{
	//DefaultPawnClass = AYHPawn::StaticClass();
	DefaultPawnClass = AYHCharacter::StaticClass();
	PlayerControllerClass = AYHPlayerController::StaticClass();
	
	//BP �ҷ��ö� _C ���̸�ȴ�. BP �� �ҷ��Դ�.
	/*static ConstructorHelpers::FClassFinder<APawn> BP_PAWN_C(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C"));
	{
		if (BP_PAWN_C.Succeeded()) {
			DefaultPawnClass = BP_PAWN_C.Class;
		}
	}*/
		
}

void AYHGameMode::PostLogin(APlayerController * NewPlayer)
{
	YHLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	YHLOG(Warning, TEXT("PostLogin End"));
}
