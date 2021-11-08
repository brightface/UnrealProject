// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../UnrealProject.h"
//#include "EngineMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YHPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API AYHPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

protected:
	virtual void BeginPlay() override;
};
