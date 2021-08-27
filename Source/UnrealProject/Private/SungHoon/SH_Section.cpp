// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_Section.h"
#include "SungHoon/SH_Character.h"
#include "SungHoon/SH_ItemBox.h"

// Sets default values
ASH_Section::ASH_Section()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // off
	SH_LOG_S(Warning);
	/*------------
		SQUARE
	-------------*/
	// ������Ʈ ����
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	// RootComponent ����
	RootComponent = Mesh;

	FString AssetPath = TEXT("/Game/PublicAsset/Chapter1/Book/StaticMesh/SM_SQUARE.SM_SQUARE");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SH_SQUARE(*AssetPath);

	if (SH_SQUARE.Succeeded())
	{
		// �ּ� ����
		Mesh->SetStaticMesh(SH_SQUARE.Object);
	}
	else
	{
		SH_LOG(Error, TEXT("Failed to load StaticMesh asset. : %s"), *AssetPath);
	}

	/*-------------------
		  BoxTrigger
	---------------------*/
	// Ʈ���ŷ� ����� �ڽ� ������Ʈ ����
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	// �ڽ� ������ �ø�
	Trigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	// ������Ʈ ���� (-> SM_SQUARE �޽��� ���߾ӿ� ��ġ�ǰ� �ɰ���)
	Trigger->SetupAttachment(RootComponent);
	// ��ġ ����
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	// �ݸ��� ä�� ����
	Trigger->SetCollisionProfileName(TEXT("SH_Trigger"));
	// BoxComponent�� �ִ� ��������Ʈ
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASH_Section::OnTriggerBeginOverlap);

	/*------------
		 GATE
	-------------*/
	FString GateAssetPath = TEXT("/Game/PublicAsset/Chapter1/Book/StaticMesh/SM_GATE.SM_GATE");
	// �ּ� ��������
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SH_GATE(*GateAssetPath);
	// �ּ��� �������� ��������
	if (!SH_GATE.Succeeded())
	{
		SH_LOG(Error, TEXT("Failed to load StaticMesh asset. : %s"), *GateAssetPath);
	}

	static FName GateSockets[] = { {TEXT("+XGate")}, {TEXT("-XGate")}, {TEXT("+YGate")}, {TEXT("-YGate") } };

	// �ش��ϴ� ���ϸ��� �ϳ��� ���鼭
	for (const FName& GateSocket : GateSockets)
	{
		// �ش��ϴ� ���ϸ��� ������ �ִ��� üũ. ������ ���
		SH_CHECK(Mesh->DoesSocketExist(GateSocket));
		// ������ �޽� ������Ʈ ����. ���ϸ��� ������
		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		// �ּ� ����
		NewGate->SetStaticMesh(SH_GATE.Object);
		// GateSocket�� �ش��ϴ� ���Ͽ� ����
		NewGate->SetupAttachment(RootComponent, GateSocket);
		// �Ǻ� �������� -80.5 ��ŭ �������� �̵� (y��)
		NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
		// �迭�� ����
		GateMeshes.Add(NewGate);

		// �� ����Ʈ���� Ʈ���� �ڽ� ����
		UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>(*GateSocket.ToString().Append(TEXT("Trigger")));
		// ������ �ڽ� ������Ʈ ũ�� ����
		NewGateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		// ������Ʈ ����, GateSocket�� �ش��ϴ� ���� ������. ����Ʈ ���� ��ġ�� ����
		NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
		// ������Ʈ ��ġ ����
		NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		// ������Ʈ �ݸ��� ä�� ����
		NewGateTrigger->SetCollisionProfileName(TEXT("SH_Trigger"));
		// Trigger�� ��Ƶδ� �迭�� �߰���.
		GateTriggers.Add(NewGateTrigger);

		// �� ����Ʈ Ʈ���Ÿ��� ��������Ʈ �Լ� ���ε���.
		NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASH_Section::OnGateTriggerBeginOverlap);
		// �� Ʈ���Ÿ��� ������Ʈ�� �±׿� ���� ���ϸ��� ������. (�������� ����)
		NewGateTrigger->ComponentTags.Add(GateSocket);

	}

	// State �ʱ�ȭ
	bNoBattle = false;

	// �ð� �ʱ�ȭ
	EnemySpawnTime = 2.0f;
	ItemBoxSpawnTime = 4.0f;
}

// ������ �۾����� ������ ������ �Ӽ��̳� Ʈ������ ������ ����ɶ� �ڵ� ȣ��Ǵ� �Լ�
void ASH_Section::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	// LOP �ﵵ����.
	SH_LOG(Warning, TEXT("Construction! : %s"), *GetName());
	// bNoBattle�� ���̸� COMPLETE����
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

// Called when the game starts or when spawned
void ASH_Section::BeginPlay()
{
	Super::BeginPlay();
	SH_LOG(Warning, TEXT("BeginPlay! : %s"), *GetName());
	// bNoBattle�� ���̸� COMPLETE����
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

void ASH_Section::SetState(ESectionState NewState)
{
	switch (NewState)
	{
	case ESectionState::READY:
		/*	TODO
			���� ������� ����ϴٰ�,
			�߾��� ���� ū Ʈ���� �ڽ��� �����ϸ� ���� ����������
		*/
		SH_LOG(Error,TEXT("Start READY state : %s"), *GetName());
		// �߾��� ���� ū Ʈ���� �ڽ� �ݸ��� ä�� ON. �۵�
		Trigger->SetCollisionProfileName(TEXT("SH_Trigger"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			// ���� �ִ� Ʈ���� �ڽ� �浹 üũ ��
			GateTrigger->SetCollisionProfileName("NoCollision");
		}
		// ���� ����.
		OperateGates(true);
		break;
		
	case ESectionState::BATTLE:
		/*	TODO
			���� �ݰ� ���� �ð��� ������ NPC�� ������ ���ڸ� ��ȯ.
			NPC�� ������ COMPLETE�� �̵�
		*/
		// ���� ū Ʈ���� �ڽ� �ݸ��� ä�� ��.
		SH_LOG(Error, TEXT("Start BATTLE state : %s"), *GetName());
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			// ���� �ִ� Ʈ���� �ڽ� �浹 üũ ��
			GateTrigger->SetCollisionProfileName("NoCollision");
		}
		// ���� ����
		OperateGates(false);

		// Ÿ�̸Ӹ� �����ϰ�, EnemySpawnTime �ð��Ŀ� ��������Ʈ �Լ��� ȣ����. OnNPCSpawn. 1���� ����ǰ���.
		GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimerHandle, FTimerDelegate::CreateUObject(
			this, &ASH_Section::OnNPCSpawn), EnemySpawnTime, false);

		// Ÿ�̸Ӹ� �����ϰ�, ItemBoxSpawnTime �ð��Ŀ� ��������Ʈ �����Լ��� ȣ����. 1���� ����ǰ���.
		GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
			
			// 600cm ���� ������ ��ǥ��
			FVector2D RandXY = FMath::RandPointInCircle(600.0f);
			// �������� ������Ŵ. �� �߾� ��ġ�� + ������ �ݰ� 600cm = 6m ��ġ��.
			GetWorld()->SpawnActor<ASH_ItemBox>(GetActorLocation() + FVector(RandXY, 60.0f), FRotator::ZeroRotator);

		}), ItemBoxSpawnTime, false);

		break;

	case ESectionState::COMPLETE:
		/*	TODO
			���� ���� ����, �� ������ ��ġ�� Trigger ����Ʈ��
			�÷��̸� �����ϸ� �̵��� ���� �������� ���ο� ���� ��ȯ.
		*/
		// ���� ū Ʈ���� �ڽ� �ݸ��� ä�� ��.
		SH_LOG(Error, TEXT("Start COMPLETE state : %s"), *GetName());
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			// ���� �ִ� Ʈ���� �ڽ� �浹 üũ ��.
			GateTrigger->SetCollisionProfileName("SH_Trigger");
		}
		// ���� ����
		OperateGates(true);
		break;
	default:
		break;
	}

	// ���� state ������Ʈ
	CurrentState = NewState;
}

void ASH_Section::OperateGates(bool bOpen)
{
	// ���� ���� �޽ø� ���鼭
	for (UStaticMeshComponent* Gate : GateMeshes)
	{
		// ���� ���°Ÿ� ȸ����Ű��, �ƴϸ� ���� ��ġ�� ����.
		Gate->SetRelativeRotation(bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::ZeroRotator);
	}
}

// �߾��� ū �ڽ�
void ASH_Section::OnTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SH_LOG_S(Warning);
	// ���� ���� ���� state�� READY���
	if (CurrentState == ESectionState::READY)
	{
		// ���� �������� �̵�
		SetState(ESectionState::BATTLE);
	}
}

// �� ���� �ִ� Ʈ���� �ڽ�
void ASH_Section::OnGateTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SH_LOG_S(Warning);
	// �ش� ������Ʈ�� �±װ� 1���� �ִ��� üũ. �´ٸ� ���
	SH_CHECK(OverlappedComponent->ComponentTags.Num() == 1);
	// �ش� �±׸��� ������
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	// �±��� ���ڿ� ���� 2���� ������. (+x, -x, +y, -y)
	FName SocketName = FName(*ComponentTag.ToString().Left(2));

	// ���� ���� �̸��� �ش��ϴ°��� �޽ÿ� ���ٸ� ����.
	if (!Mesh->DoesSocketExist(SocketName))
	{
		return;
	}
	
	// ���ϸ� �ش��ϴ� ��ġ�� ����
	FVector NewLocation = Mesh->GetSocketLocation(SocketName);

	// �浹 ����� ���� ����
	TArray<FOverlapResult> OverlapResults;
	// ���ǽ� ������ ����
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectQueryParam(FCollisionObjectQueryParams::InitType::AllObjects);
	
	// ������Ű���� ��ġ�� �浹üũ�� �غ�.
	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults, // ����� ����
		NewLocation, // �浹üũ�� �����ϴ� �߽���
		FQuat::Identity, // ȸ����
		ObjectQueryParam, // ��� Object �˻�
		FCollisionShape::MakeSphere(775.0f), // ��ü
		CollisionQueryParam // ���� �ڽ� ���� �� Ÿ���� ����
	);

	// �浹�Ȱ� ���ٸ�
	if (!bResult)
	{
		// ���ο� ������ ���������ش�.
		auto NewSection = GetWorld()->SpawnActor<ASH_Section>(NewLocation, FRotator::ZeroRotator);
	}
	// �浹�Ȱ� �ִٸ�, �̹� ������� ������ �����Ѵٴ� �ǹ�.
	else
	{
		SH_LOG(Warning, TEXT("New section area is not empty. already existed"));
	}
}

// AI ���� �Լ�
void ASH_Section::OnNPCSpawn()
{
	// ���� ���� �߾� ��ġ�� + 88.0f ���� ����, ȸ������ �⺻������ ���͸�������Ų��.
	GetWorld()->SpawnActor<ASH_Character>(GetActorLocation() + FVector::UpVector*88.0f, FRotator::ZeroRotator);
}

