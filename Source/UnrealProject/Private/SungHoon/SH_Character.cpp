// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_Character.h"

// Sets default values
ASH_Character::ASH_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Print LOG
	SH_LOG(Warning, TEXT("Execute SH_Character Constructor!"));


	// Create component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SH_SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("SH_CAMERA"));

	// Attachment
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	// Set up values
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f),
		FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f; // distance
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f)); // rotation

	// Add Mesh asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SH_CARDBOARD(TEXT(
		"/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"
	));
	if (SH_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SH_CARDBOARD.Object);
	}


	// Add Animation asset (AnimationBlueprint, UAnimInstance)
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint); // A_BP ��� ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> SH_CARDBOARD_ANIM(TEXT(
		"/Game/SungHoon/Animation/SH_WarriorAnimBlueprint.SH_WarriorAnimBlueprint_C"
	));
	if (SH_CARDBOARD_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(SH_CARDBOARD_ANIM.Class);
	}

	// Set default ��Ʈ�� ��� ����. DIABLO ���
	SetControlMode(EControlMode::GTA);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f; // ȸ�� �ӵ�

	// for jump speed
	GetCharacterMovement()->JumpZVelocity = 450.0f;
}

// Called when the game starts or when spawned
void ASH_Character::BeginPlay()
{
	Super::BeginPlay();

}

// Setting View
void ASH_Character::SetControlMode(const EControlMode& NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		SH_LOG(Error, TEXT("GTA Mode"));

		//SpringArm->TargetArmLength = 1000.0f;
		//SpringArm->SetRelativeRotation(FRotator::ZeroRotator); // ���� ������ ������.
		ArmLengthTo = 600.0f; // distance
		SpringArm->bUsePawnControlRotation = true; // ��Ʈ�� ȸ������ �����ϴ�.
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bInheritRoll = true;

		// ī�޶�� ���� �浹�� üũ����. ���� ������ �˾Ƽ� ���εʡ�
		SpringArm->bDoCollisionTest = true;

		// Pawn ������ ���ۺ��� ȸ�� ����. (���� ��� ����. default����)
		bUseControllerRotationYaw = false;

		// CharacterMovement�� �ִ� ����� �̿�����.
		// ī�޶� �����̴� �������� �޽ø� �����̰� �ϴ� �����. true ����. (���� false��)
		GetCharacterMovement()->bOrientRotationToMovement = true;

		// 45���� ���ܼ� ȸ���ϴ°��� �ذ��ϱ� ����, �ε巴�� ȸ���ϴ� ���. GTA�� ������ �����Ƿ� ��������.
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ȸ���ӵ� ����
		break;

	case EControlMode::DIABLO:
		SH_LOG(Error, TEXT("DIABLO Mode"));

		//SpringArm->TargetArmLength = 800.0f;
		//SpringArm->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f)); // �Ʒ��� ����.
		ArmLengthTo = 900.0f; // distance
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f); // ī�޶� ����
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bInheritRoll = false;

		// ī�޶�� ���� �浹�� üũ����. ���� ������ �˾Ƽ� ���εǴ°� ��.
		SpringArm->bDoCollisionTest = false;

		// Pawn ������ ���ۺ��� ȸ�� ����. (���� ��� ����)
		// ��� �ؿ��� bUseControllerDesiredRotation�� �Ѽ� �ذ���. �Ѵ� ���������� �ȵȵ�!
		bUseControllerRotationYaw = false;

		// CharacterMovement�� �ִ� ����� �̿�����.
		// ī�޶� �����̴� �������� �޽ø� �����̰� �ϴ� �����. false. ������ �����̹Ƿ�.
		GetCharacterMovement()->bOrientRotationToMovement = false;

		// 45���� ���ܼ� ȸ���ϴ°��� �ذ��ϱ� ����, �ε巴�� ȸ���ϴ� ���. ������.
		GetCharacterMovement()->bUseControllerDesiredRotation = true; // �ε巯�� ȸ���� ����

		// ĳ���� �޽��� ȸ���ӵ� ���� bUseControllerDesiredRotation�� ��ȯ �ӵ��� �ǹ�.
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	default:
		break;
	}
}

// Called every frame
void ASH_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �� �����Ӹ��� ī�޶� ������ �Ÿ� ���
	// InterpTo(���� ��, ���� ��ǥ��, �ð�, �����ӵ�)
	 SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		break;

	case EControlMode::DIABLO:
		/*
			DIABLO ����� �Է°��� �ް� �ٷ� �����̰� ȸ���ϴ°� �ƴ϶�,
			�ش��ϴ� ȸ���� �����Ӱ��� ��� ó���� �ڿ�, ���������� Tick����
			������� �̿��ؼ� �̵��ϰ� ȸ���ϵ��� ����. �׷��� ���� ��������
			Tick�Լ��� �ִ�. GTA�� �ƴ�. GTA�� �Է��Լ��� ����.
		*/

		SpringArm->SetRelativeRotation(FMath::RInterpTo(SpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed));

		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			// rotation (�޽ð� ���ư�) 
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			// move (���� �̵�)
			AddMovementInput(DirectionToMove);
		}
		break;

	default:
		break;
	}

}

// Called to bind functionality to input
void ASH_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// for movement
	PlayerInputComponent->BindAxis(TEXT("UpDown_SH"), this, &ASH_Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight_SH"), this, &ASH_Character::LeftRight);

	// for rotation
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASH_Character::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASH_Character::Turn);

	// for changing view button
	PlayerInputComponent->BindAction(TEXT("SH_ViewChange"), EInputEvent::IE_Pressed, this, &ASH_Character::ViewChange);

	// for jump
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

// for forward, back move
void ASH_Character::UpDown(const float NewAxisValue)
{
	// AddMovementInput(GetActorForwardVector(), NewAxisValue);
	// AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//AddMovementInput(GetActorForwardVector(), NewAxisValue); // �޽ð� �ٶ󺸴� ���� �������� ������.

		// ���� ��Ʈ�ѷ��� ȸ������ �����ͼ� �������ͷ� ������ ���ؿ�. �� �������� �̵���.
		//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
		break;

	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;

	default:
		break;
	}
}

// for left, right move
void ASH_Character::LeftRight(const float NewAxisValue)
{
	// AddMovementInput(GetActorRightVector(), NewAxisValue);
	// AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//AddMovementInput(GetActorRightVector(), NewAxisValue); // �޽��� ������ ������ �������� ������.

		// ���� ��Ʈ�ѷ��� ȸ������ �����ͼ� �������ͷ� ������ ���ؿ�. �� �������� �̵���.
		//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;

	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;

	default:
		break;
	}
}

// Pitch (���Ʒ�)
void ASH_Character::LookUp(const float NewAxisValue)
{
	// ���Ʒ� ȸ���� Y�� ���� ȸ��(���� ��)
	// AddControllerPitchInput(NewAxisValue);

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;

	case EControlMode::DIABLO:
		break;

	default:
		break;
	}
}

// Yaw (�¿� ���ۺ���)
void ASH_Character::Turn(const float NewAxisValue)
{
	// ������ ȸ�� Z�� ���� ȸ�� (���� ��)
	// AddControllerYawInput(NewAxisValue);
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;

	case EControlMode::DIABLO:
		break;

	default:
		break;
	}
}

void ASH_Character::ViewChange()
{
	// Print LOG
	SH_LOG_S(Error);

	switch (CurrentControlMode)
	{
		// ���� ��尡 GTA���
	case EControlMode::GTA:
		// for DIABLO
		/*
			�Ʒ� ��Ʈ�ѷ��� ȸ������ �������ִ� ������ ����?
		*/
		// Controller�� rotation���� ���� ������ Rotation������ ����.
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);;
		break;

		// ���� ��尡 DIABLO���
	case EControlMode::DIABLO:
		// for GTA
		/*
			DIABLO�� SpringArm�� �������� ȸ���ϱ� ����.
			�̰� �ٽ� ��Ʈ�ѷ��� ȸ�������� �������� �ʿ䰡 ����.
			�̰� �����ָ� GTA�� ��ȯ�Ҷ� �׻� Default ī�޶� ��������,
			���鼦�� ����.
			��, ī�޶��� ���� ������ �״�� �����´ٸ�, ���� �ڿ����������°���.
		*/
		// ���� SpringArm�� ȸ������ ControlRotation ������ ����.
		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		SetControlMode(EControlMode::GTA);;
		break;

	default:
		break;
	}
}