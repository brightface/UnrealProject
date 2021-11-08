// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../UnrealProject.h"
#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "YHGameMode.generated.h"


/**
 * 
 */
UCLASS()
class UNREALPROJECT_API AYHGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
		AYHGameMode();
		virtual void PostLogin(APlayerController* NewPlayer) override;
	
};
