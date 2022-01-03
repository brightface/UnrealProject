// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "EngineMinimal.h" // �� ���� ����� ���� (0811)

#pragma region SungHoon area

UENUM(BlueprintType)
enum class ESH_CharacterState : uint8
{
	PREINIT,
	LOADING,
	READY,
	DEAD
};


// LOG macro by SungHoon
DECLARE_LOG_CATEGORY_EXTERN(LOG_SH, Log, All);

// ���� 2���� �ֱ� ���� ��ũ��
#define SHLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(" line)"))

/// ������ ����ϰԵ� ��ũ�� ��. UE_LOG ������ �����;���.
// ��� �Լ��� ���ٿ��� ����ƴ����� ���
#define SH_LOG_S(Verbosity) UE_LOG(LOG_SH, Verbosity, TEXT("%s"), *SHLOG_CALLINFO)
// printf ������ �߰��� ���. UE_LOG�� ������ ������. 
#define SH_LOG(Verbosity, Format, ...) UE_LOG(LOG_SH, Verbosity, TEXT("%s, %s"), *SHLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
// �ش��ϴ� ���ǽ� Expr�� �����̸� �Ʒ� ��ũ�� �Լ� ���θ� ������.
#define SH_CHECK(Expr, ...) {if(!(Expr)){SH_LOG(Error,TEXT("ASSERTION : %s"),TEXT("'"#Expr"'")); return __VA_ARGS__;}}

#pragma endregion



#pragma region JongGyun area

DECLARE_LOG_CATEGORY_EXTERN(LOG_JG, Log, All);
#define JGLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(")+ FString::FromInt(__LINE__) + TEXT(")"))
#define JGLOG_S(Verbosity) UE_LOG(LOG_JG, Verbosity, TEXT("%s"), *JGLOG_CALLINFO)
#define JGLOG(Verbosity, Format, ...) UE_LOG(LOG_JG, Verbosity, TEXT("%s, %s"), *JGLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#pragma endregion


#pragma region YongHwan area

DECLARE_LOG_CATEGORY_EXTERN(LOG_YH, Log, All);
#define YHLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(")+ FString::FromInt(__LINE__) + TEXT(")"))
#define YHLOG_S(Verbosity) UE_LOG(LOG_YH, Verbosity, TEXT("%s"), *YHLOG_CALLINFO)
#define YHLOG(Verbosity, Format, ...) UE_LOG(LOG_YH, Verbosity, TEXT("%s, %s"), *YHLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
// �ش��ϴ� ���ǽ� Expr�� �����̸� �Ʒ� ��ũ�� �Լ� ���θ� ������.
#define YHCHECK(Expr, ...) {if(!(Expr)){ YHLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}
#pragma endregion