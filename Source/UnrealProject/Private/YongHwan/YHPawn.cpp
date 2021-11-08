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

	// 애니메이션 모드 설정. 애니메이션 블루프린트
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님인스턴스 블루프린트 이게 Beginplay에서 BP 말고 경로 자체로 애니메이션 엮여준것인데 따로 이건 BP로 한것.
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM_YH(TEXT(
		"/Game/YongHwan/BP/WarriorAnimBlueprint_YH.WarriorAnimBlueprint_YH_C"));

	// 애님 인스턴스를 잘 가져왔다면
	if (WARRIOR_ANIM_YH.Succeeded())
	{
		// 메시에 있는 애님 인스턴스 클래스에 워리어 애님 인스턴스를 등록.
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
	AddMovementInput(GetActorForwardVector(), NewAxisValue); //이거 없으면 바인딩 해도 실제 캐릭터는 안움직여
	
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

