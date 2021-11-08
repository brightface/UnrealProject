// Fill out your copyright notice in the Description page of Project Settings.


#include "YongHwan/YHGameMode.h"
//#include "YongHwan/YHPawn.h"
#include "YongHwan/YHCharacter.h"
#include "Yonghwan/YHPlayerController.h"
//게임모드 생성자에서 플레이어컨드롤러 속성을 yh플레이어 컨트롤러 클래스값으로 변경

AYHGameMode::AYHGameMode()
{
	//DefaultPawnClass = AYHPawn::StaticClass();
	DefaultPawnClass = AYHCharacter::StaticClass();
	PlayerControllerClass = AYHPlayerController::StaticClass();
	
	//BP 불러올때 _C 붙이면된다. BP 폰 불러왔다.
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
