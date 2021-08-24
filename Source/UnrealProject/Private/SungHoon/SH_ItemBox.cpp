// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_ItemBox.h"
#include "SungHoon/SHWeapon.h" 
#include "SungHoon/SH_Character.h"

// Sets default values
ASH_ItemBox::ASH_ItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // tick�� ������.

	// ������Ʈ ����
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SH_TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SH_BOX"));
	
	// ��Ʈ ������Ʈ ����, ��Ÿ ������Ʈ ����
	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	// �ڽ� ������Ʈ ũ�� ����
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	Box->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));

	// ����ƽ �޽ÿ� ����� �ּ� ���� ��������
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SH_ITEM_BOX(TEXT(
		"/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"
	));
	if (SH_ITEM_BOX.Succeeded())
	{
		// ����ƽ �޽� ������Ʈ�� �޽� �ּ� ����
		Box->SetStaticMesh(SH_ITEM_BOX.Object);
	}
	
	// �ڽ� ������Ʈ�� ���� ��ġ�� ����, ������ ���� ��ġ�� �������� ��ġ���� �ȴ�.
	Trigger->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	// ä�� ����
	Trigger->SetCollisionProfileName(TEXT("SH_ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	// SHWeapon Ŭ���� ������ ������. ������� �߰��ؾ���.
	WeaponItemClass = ASHWeapon::StaticClass();

	/*-------------
		Effect
	--------------*/
	// ��ƼŬ ������Ʈ ����
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SH_EFFECT"));
	// ������Ʈ ����
	Effect->SetupAttachment(RootComponent);

	// ������Ʈ�� ���� �ּ� ���� ��������
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SH_CHESTOPEN(TEXT(
		"/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"
	));
	if (SH_CHESTOPEN.Succeeded())
	{
		// ��ƼŬ �ּ� ����
		Effect->SetTemplate(SH_CHESTOPEN.Object); // effect�� template�̴�
		// �ڵ� Ȱ��ȭ�� ����.
		Effect->bAutoActivate = false;
	}
}

// Called when the game starts or when spawned
void ASH_ItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASH_ItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASH_ItemBox::OnCharacterOverlap);
}

// Called every frame
void ASH_ItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASH_ItemBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// ��ġ�� �α׸� ��쵵�� �غ���.
	SH_LOG_S(Error);

	// ��ģ ���� ���͸� �����ͼ� ĳ����
	auto SHCharacter = Cast<ASH_Character>(OtherActor);
	// ���������� ĳ���� �ƴٸ� ���
	SH_CHECK(SHCharacter != nullptr);

	// ���� Ŭ���� ������ ����� ���� �ִٸ�
	if (WeaponItemClass != nullptr && SHCharacter != nullptr)
	{
		// ĳ���Ͱ� ���⸦ ���� �� �ִٸ� (���Ⱑ ���� ���ٸ�)
		if (SHCharacter->CanSetWeapon())
		{
			// ���� ���͸� ������.
			auto NewWeapon = GetWorld()->SpawnActor<ASHWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			// ������ ���� ���͸� ĳ���Ϳ� ����
			SHCharacter->SetWeapon(NewWeapon);

			// ����Ʈ Ȱ��ȭ
			Effect->Activate(true);
			// ����ƽ �޽� ����. ��ӹ����͵� ����
			Box->SetHiddenInGame(true, true);
			// ������ �ڽ� ���Ϳ� ���� �浹�� ���� -> �̺�Ʈ �߻� ����
			SetActorEnableCollision(false);
			// ��������Ʈ ���. OnEffectFinished�� �����Ŵ.
			Effect->OnSystemFinished.AddDynamic(this, &ASH_ItemBox::OnEffectFinished);
		}
		// ���⸦ �̹� ������ �־ �� ���� �� ���ٸ�
		else
		{
			// �α׸� ����
			SH_LOG(Error, TEXT("%s can't equip weapon currently. already had it."), *SHCharacter->GetName());
		}
	}
}

void ASH_ItemBox::OnEffectFinished(UParticleSystemComponent * PSystem)
{
	// ���� ���͸� �ı���.
	Destroy();
}