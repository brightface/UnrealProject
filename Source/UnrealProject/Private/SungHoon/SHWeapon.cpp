// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SHWeapon.h"

// Sets default values
ASHWeapon::ASHWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // ���� �ʿ����

	// ������Ʈ ����
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SH_WEAPON"));
	// root component ����
	RootComponent = Weapon;
	// �ּ� ���� ��������
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SH_ITEM_WEAPON(TEXT(
		"/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_Fencer/SK_Blade_Fencer.SK_Blade_Fencer"
	));

	if (SH_ITEM_WEAPON.Succeeded())
	{
		// �޽� ���
		Weapon->SetSkeletalMesh(SH_ITEM_WEAPON.Object);
	}
	// �浹üũ ����
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ASHWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASHWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
