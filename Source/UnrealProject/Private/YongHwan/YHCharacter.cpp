// Fill out your copyright notice in the Description page of Project Settings.


#include "YongHwan/YHCharacter.h"

// Sets default values
AYHCharacter::AYHCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SHSPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("SHCAMERA"));
	SpringArm->SetupAttachment(GetCapsuleComponent()); //Capsule->GetCapuleComponent
	Camera->SetupAttachment(SpringArm);

	//���� ���̶� �ٸ��� GetMesh()��. ���� Mesh->SetRelative... ����.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT(
		"/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{

		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	// �ִϸ��̼� ��� ����. �ִϸ��̼� �������Ʈ
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// �ִ��ν��Ͻ� �������Ʈ �̰� Beginplay���� BP ���� ��� ��ü�� �ִϸ��̼� �����ذ��ε� ���� �̰� BP�� �Ѱ�.
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM_YH(TEXT(
		"/Game/YongHwan/BP/WarriorAnimBlueprint_YH.WarriorAnimBlueprint_YH_C"));

	// �ִ� �ν��Ͻ��� �� �����Դٸ�
	if (WARRIOR_ANIM_YH.Succeeded())
	{
		// �޽ÿ� �ִ� �ִ� �ν��Ͻ� Ŭ������ ������ �ִ� �ν��Ͻ��� ���.
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM_YH.Class);
	}

	//SetControlMode(0);
	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	SetControlMode(EControlMode::DIABLO);
}

void AYHCharacter::SetControlMode(EControlMode NewControlMode) {
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//SpringArm->TargetArmLength = 450.0f;
		//SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		ArmLengthTo = 450.0f;

		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		//45�� ������ �������� ȸ���ϱ� ������ �� �ڵ带 �־ �ε巴�� ȸ���� ����.
		GetCharacterMovement()->bUseControllerDesiredRotation = false;

		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::DIABLO:
		//SpringArm->TargetArmLength = 800.0f;
		//SpringArm->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f));
		ArmLengthTo = 800.0f;
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;

		//45�� ������ �������� ȸ���ϱ� ������ �� �ڵ带 �־ �ε巴�� ȸ���� ����.
		bUseControllerRotationYaw = false; //�̰� �� �ȸ���. �ȸԴ´�. ������Ƽ������ üũ���� ����ߵ�.
		GetCharacterMovement()->bOrientRotationToMovement = false; //�̰� ��� �ȴ�. �̰͵� �ȸԾ�.
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

		bUseControllerRotationYaw = true;
		break;
	}
}
// Called when the game starts or when spawned
void AYHCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AYHCharacter::SetControlMode(int32 ControlMode)
{
	if (ControlMode == 0)
	{
		SpringArm->TargetArmLength = 450.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	}
}
// Called every frame
void AYHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:
		SpringArm->GetRelativeRotation() = FMath::RInterpTo(SpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed);
		break;

	}
	switch (CurrentControlMode)
	{
	case EControlMode::DIABLO:

		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}

}

// Called to bind functionality to input
void AYHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("ViewChange_YH"), EInputEvent::IE_Pressed, this, &AYHCharacter::ViewChange);
	PlayerInputComponent->BindAxis(TEXT("UpDown_YH"), this, &AYHCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight_YH"), this, &AYHCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AYHCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AYHCharacter::Turn);

}
void AYHCharacter::UpDown(float NewAxisValue) {
	YHLOG(Warning, TEXT("%f"), NewAxisValue);
	
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;
	}
	
	//6�� �պκ�
	//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue); //�̰� ������ ���ε� �ص� ���� ĳ���ʹ� �ȿ�����
	//AddMovementInput(GetActorForwardVector(), NewAxisValue); //�̰� ������ ���ε� �ص� ���� ĳ���ʹ� �ȿ�����

}

void AYHCharacter::LeftRight(float NewAxisValue) {
	
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;
	}
	
	YHLOG(Warning, TEXT("%f"), NewAxisValue);
	
	//6�� �պκ�
	//AddMovementInput(GetActorRightVector(), NewAxisValue);
	//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);

}
void AYHCharacter::LookUp(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;
	}
	
	// 6�� �պκ�
	//AddControllerPitchInput(NewAxisValue);
}

void AYHCharacter::Turn(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;
	}
	
	// 6�� �պκ�
	//AddControllerYawInput(NewAxisValue);
}
void AYHCharacter::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//�ε巴�� ȭ�� ��ȯ�ϱ� ���� �߰��Ѵ�.
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		//�ε巴�� ȭ�� ��ȯ�ϱ� ���� �߰��Ѵ�.
		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		SetControlMode(EControlMode::GTA);
		break;
	}
}