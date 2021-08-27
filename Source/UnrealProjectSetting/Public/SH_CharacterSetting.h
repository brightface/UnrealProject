// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SH_CharacterSetting.generated.h"

/**
 * 
 */
// �ҷ����� UnrealProject�� �̸��� INI ���ϸ��� ����.
UCLASS(config=UnrealProject)
class UNREALPROJECTSETTING_API USH_CharacterSetting : public UObject
{
	GENERATED_BODY()
	
public:
	USH_CharacterSetting();

	// ĳ���� �ּ� ����
	UPROPERTY(config)
	TArray<FSoftObjectPath> CharacterAssets;
};
