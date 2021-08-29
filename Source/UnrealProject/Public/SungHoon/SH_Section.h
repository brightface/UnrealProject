// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../UnrealProject.h" // for EngineMinimal
#include "GameFramework/Actor.h"
#include "SH_Section.generated.h"

UCLASS()
class UNREALPROJECT_API ASH_Section : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASH_Section();

	// ������ �۾����� ������ ������ �Ӽ��̳� Ʈ������ ������ ����ɶ� �ڵ� ȣ��Ǵ� �Լ�
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// ���� state�� ���� ������ ����
	enum class ESectionState : uint8
	{
		READY = 0,
		BATTLE,
		COMPLETE
	};

	// ���� ����
	void SetState(ESectionState NewState);
	// ���� ����.
	ESectionState CurrentState = ESectionState::READY;
	// ���� ���� �ݴ� �Լ�. �Է°� ������ �⺻ true
	void OperateGates(bool bOpen = true);

	// �߾� ū �ڽ�
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// �� ���� �ִ� �ڽ�
	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// NPC �����Լ�
	void OnNPCSpawn();

	// NPC�� �ı��Ǿ����� ȣ���� �Լ�
	UFUNCTION()
	void OnKeyNPCDestroyed(AActor* DestoryedActor);

private:
	// for SM_SQUARE
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	// for Box Trigger
	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	UBoxComponent* Trigger;

	// for SM_GATE
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TArray<UStaticMeshComponent*> GateMeshes;

	// for Box Trigger
	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	TArray<UBoxComponent*> GateTriggers;

	// ���� ���� �ٷ� �Ϸ� ������Ʈ���� ������ �� �ִ� ����
	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
	bool bNoBattle;


	// AI Spawn Time
	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float EnemySpawnTime;

	// Item Spawn Time
	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float ItemBoxSpawnTime;

	// Ÿ�̸� �ڵ� ����
	FTimerHandle SpawnNPCTimerHandle = {};
	FTimerHandle SpawnItemBoxTimerHandle = {};
};
