// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "SFountain.generated.h" // �𸮾� ������Ʈ ����3 : generated.h ��� �߰�

UCLASS() // �𸮾� ������Ʈ ����1 : Ŭ���� ���� ��ũ��
class UNREALPROJECT_API ASFountain : public AActor // �𸮾� ������Ʈ ����2 : Ŭ���� �̸� ��ũ�� // �𸮾� ������Ʈ ����4 : �ܺ� ��⿡���� ���� ����
{
	GENERATED_BODY() // �𸮾� ������Ʈ ����1 : Ŭ���� ���� ��ũ��
	
public:	
	// Sets default values for this actor's properties
	ASFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Water;

	// ����
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* Light;

	// ����Ʈ
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* Splash;

	UPROPERTY(EditAnywhere, Category = ID)
	int32 ID;
};
