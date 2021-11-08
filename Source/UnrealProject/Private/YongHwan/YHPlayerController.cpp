// Fill out your copyright notice in the Description page of Project Settings.


#include "YongHwan/YHPlayerController.h"

void AYHPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	YHLOG_S(Warning);
}

void AYHPlayerController::OnPossess(APawn * aPawn)
{

	YHLOG_S(Warning);
	Super::OnPossess(aPawn);
}

void AYHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}