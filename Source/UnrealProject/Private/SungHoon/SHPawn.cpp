// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SHPawn.h"

// Sets default values
ASHPawn::ASHPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SHCAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SHMESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("SHMOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SHSPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("SHCAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);

	// �ѹ��� ���尡��
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	// ���̷�Ż �޽� �ּ� ã�ƿ���
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));

	// �޽� �ּ��� ã�ƿ�����
	if (SK_CARDBOARD.Succeeded())
	{
		// ���� �޽ÿ� �ּ��� ���. ȭ�鿡 ��µ�.
		Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	// �ִϸ��̼� ��� ����. �ִϸ��̼� �������Ʈ
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
	// �ִ��ν��Ͻ� ������ ã�ƿ�.
	static ConstructorHelpers::FClassFinder<UAnimInstance> SH_WARRIOR_ANIM(TEXT("/Game/SungHoon/Animation/SH_WarriorAnimBlueprint.SH_WarriorAnimBlueprint_C"));

	// �ִ� �ν��Ͻ��� �� �����Դٸ�
	if (SH_WARRIOR_ANIM.Succeeded())
	{
		// �޽ÿ� �ִ� �ִ� �ν��Ͻ� Ŭ������ ������ �ִ� �ν��Ͻ��� ���.
		Mesh->SetAnimInstanceClass(SH_WARRIOR_ANIM.Class);
	}


}

// Called when the game starts or when spawned
void ASHPawn::BeginPlay()
{
	Super::BeginPlay();
	
	// �̰� ���� �����ϱ�.
	//Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/PublicAsset/Chapter5/WarriorRun.WarriorRun"));

	//if (AnimAsset != nullptr)
	//{
	//	// �ִϸ��̼� ������ �Ž����� ����.
	//	Mesh->PlayAnimation(AnimAsset, true);
	//}
}

// Called every frame
void ASHPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASHPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SH_LOG_S(Warning);
}

void ASHPawn::PossessedBy(AController* NewController)
{
	SH_LOG_S(Warning);
	Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void ASHPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown_SH"), this, &ASHPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight_SH"), this, &ASHPawn::LeftRight);
}

void ASHPawn::UpDown(float NewAxisValue)
{
	SH_LOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void ASHPawn::LeftRight(float NewAxisValue)
{
	SH_LOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}
