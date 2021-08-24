// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal
#include "GameFramework/Actor.h"
#include "SH_ItemBox.generated.h"


UCLASS()
class UNREALPROJECT_API ASH_ItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASH_ItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// �ڽ� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;

	// ����ƽ�޽� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;

	// ����Ʈ ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;

	// SHWeapon Ŭ������ �װ� ��ӹ޴� Ŭ�������� ������� ��������.
	UPROPERTY(EditInstanceOnly, Category = Box)
	TSubclassOf<class ASHWeapon> WeaponItemClass; // ���漱��

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);

};
