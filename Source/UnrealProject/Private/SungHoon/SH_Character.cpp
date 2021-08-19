// Fill out your copyright notice in the Description page of Project Settings.


#include "SungHoon/SH_Character.h"

// Sets default values
ASH_Character::ASH_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SH_LOG(Warning, TEXT("Execute SH_Character Constructor!"));


	// Create component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SH_SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("SH_CAMERA"));

	// Attachment
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	// Set up values
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
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


	// Add Animation asset
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint); // A_BP ��� ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> SH_CARDBOARD_ANIM(TEXT(
		"/Game/SungHoon/Animation/SH_WarriorAnimBlueprint.SH_WarriorAnimBlueprint_C"
	));
	if (SH_CARDBOARD_ANIM.Succeeded())
	{
		/// Added AnimInstance
		GetMesh()->SetAnimInstanceClass(SH_CARDBOARD_ANIM.Class);
	}

	// Set default ��Ʈ�� ��� ����. DIABLO ���
	SetControlMode(EControlMode::DIABLO);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f; // ȸ�� �ӵ�
}

// Called when the game starts or when spawned
void ASH_Character::BeginPlay()
{
	Super::BeginPlay();

}

void ASH_Character::SetControlMode(const EControlMode& NewControlMode)
{
	CurrentControlMode = NewControlMode;


	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		SH_LOG_S(Error);
		ArmLengthTo = 600.0f; // distance
		//SpringArm->SetRelativeRotation(FRotator::ZeroRotator); // ����
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bInheritRoll = true;

		// ī�޶�� ���� �浹�� üũ����. ���� ������ �˾Ƽ� ���εʡ�
		SpringArm->bDoCollisionTest = true;

		// Pawn ������ ���ۺ��� ȸ�� ����. (���� ��� ����)
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;

	case EControlMode::DIABLO:

		ArmLengthTo = 800.0f; // distance
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		// SpringArm->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f)); // ����
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bInheritRoll = false;

		// ī�޶�� ���� �浹�� üũ����. ���� ������ �˾Ƽ� ���εʡ�
		SpringArm->bDoCollisionTest = false;

		// Pawn ������ ���ۺ��� ȸ�� ����. (���� ��� ����)
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true; // �ε巯�� ȸ���� ����

		GetCharacterMovement()->bOrientRotationToMovement = false;
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
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		break;

	case EControlMode::DIABLO:
		SpringArm->AddRelativeRotation(FMath::RInterpTo(SpringArm->GetComponentRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed));

		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
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

	PlayerInputComponent->BindAxis(TEXT("UpDown_SH"), this, &ASH_Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight_SH"), this, &ASH_Character::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASH_Character::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASH_Character::Turn);

	PlayerInputComponent->BindAction(TEXT("SH_ViewChange"), EInputEvent::IE_Pressed, this, &ASH_Character::ViewChange);
}

void ASH_Character::UpDown(const float NewAxisValue)
{
	// AddMovementInput(GetActorForwardVector(), NewAxisValue);
	// AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(FRotator(0.0f,GetControlRotation().Yaw,0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
		break;

	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		break;

	default:
		break;
	}
}

void ASH_Character::LeftRight(const float NewAxisValue)
{
	// AddMovementInput(GetActorRightVector(), NewAxisValue);
	// AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);

	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
		break;

	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		break;

	default:
		break;
	}
}

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
	SH_LOG_S(Error);
	switch (CurrentControlMode)
	{
		// ���� ��尡 GTA���
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);;
		break;

		// ���� ��尡 DIABLO���
	case EControlMode::DIABLO:
		GetController()->SetControlRotation(SpringArm->GetComponentRotation());
		SetControlMode(EControlMode::GTA);;
		break;

	default:
		break;
	}
}