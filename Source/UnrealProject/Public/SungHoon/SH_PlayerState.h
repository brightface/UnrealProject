// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h"
#include "GameFramework/PlayerState.h"
#include "SH_PlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);


/**
 * 
 */
UCLASS()
class UNREALPROJECT_API ASH_PlayerState : public APlayerState
{
	GENERATED_BODY()
	

public:
	ASH_PlayerState();

	int32 GetGameScore() const;
	int32 GetCharacterLevel() const;

	// exp 관련
	float GetExpRatio() const; // 현재 경험치 비율 반환
	bool AddExp(int32 IncomeExp);

	// Score
	void AddScore();

	// 플레이어 데이터 초기화 함수
	void InitPlayerData();

	// 델리게이트 변수 선언
	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;

	// 경험치 변수
	UPROPERTY(Transient)
	int32 Exp;

private:
	// 레벨 설정
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FSHCharacterData* CurrentStatData;
};
