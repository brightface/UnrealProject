// Fill out your copyright notice in the Description page of Project Settings.


#include "YongHwan/YHPawn.h"

// Sets default values
AYHPawn::AYHPawn()
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

	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT(
		"/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{
		
		Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	// �ִϸ��̼� ��� ����. �ִϸ��̼� �������Ʈ
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// �ִ��ν��Ͻ� �������Ʈ �̰� Beginplay���� BP ���� ��� ��ü�� �ִϸ��̼� �����ذ��ε� ���� �̰� BP�� �Ѱ�.
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM_YH(TEXT(
		"/Game/YongHwan/BP/WarriorAnimBlueprint_YH.WarriorAnimBlueprint_YH_C"));

	// �ִ� �ν��Ͻ��� �� �����Դٸ�
	if (WARRIOR_ANIM_YH.Succeeded())
	{
		// �޽ÿ� �ִ� �ִ� �ν��Ͻ� Ŭ������ ������ �ִ� �ν��Ͻ��� ���.
		Mesh->SetAnimInstanceClass(WARRIOR_ANIM_YH.Class);
	}


}

// Called when the game starts or when spawned
void AYHPawn::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/PublicAsset/Chapter5/WarriorRun.WarriorRun"));
	if (AnimAsset != nullptr)
	{
		Mesh->PlayAnimation(AnimAsset, true);
	}
}

// Called every frame
void AYHPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYHPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown_YH"), this, &AYHPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight_YH"), this, &AYHPawn::LeftRight);

}

void AYHPawn::UpDown(float NewAxisValue) {
	YHLOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(GetActorForwardVector(), NewAxisValue); //�̰� ������ ���ε� �ص� ���� ĳ���ʹ� �ȿ�����
	
}

void AYHPawn::LeftRight(float NewAxisValue) {
	YHLOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}

void AYHPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	YHLOG_S(Warning);
}

void AYHPawn::PossessedBy(AController * NewController)
{
	YHLOG_S(Warning);
	Super::PossessedBy(NewController);

}

