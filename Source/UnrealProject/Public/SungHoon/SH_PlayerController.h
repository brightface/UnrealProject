// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal.h & macro
#include "GameFramework/PlayerController.h"
#include "SH_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API ASH_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASH_PlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

	class USH_HUDWidget* GetHUDWidget() const;
	
	// �÷��̾ NCP�� �׿�����
	void NPCKill(class ASH_Character* KilledNPC) const;
	// ���� ���ھ� �߰�
	void AddGameScore() const;

protected:
	virtual void BeginPlay() override;
	//virtual void SetupInputComponent() override;

	// HUD ���� Ŭ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class USH_HUDWidget> HUDWidgetClass;

private:


private:
	UPROPERTY()
	class USH_HUDWidget* HUDWidget;

	UPROPERTY()
	class ASH_PlayerState* SHPlayerState;
		
};
