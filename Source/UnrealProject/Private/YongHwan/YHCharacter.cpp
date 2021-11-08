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

	//여긴 폰이랑 다르게 GetMesh()다. 폰은 Mesh->SetRelative... 였다.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT(
		"/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{

		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	// 애니메이션 모드 설정. 애니메이션 블루프린트
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애님인스턴스 블루프린트 이게 Beginplay에서 BP 말고 경로 자체로 애니메이션 엮여준것인데 따로 이건 BP로 한것.
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM_YH(TEXT(
		"/Game/YongHwan/BP/WarriorAnimBlueprint_YH.WarriorAnimBlueprint_YH_C"));

	// 애님 인스턴스를 잘 가져왔다면
	if (WARRIOR_ANIM_YH.Succeeded())
	{
		// 메시에 있는 애님 인스턴스 클래스에 워리어 애님 인스턴스를 등록.
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
		//45도 단위로 끊어져서 회전하기 때문이 이 코드를 넣어서 부드럽게 회전을 보완.
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

		//45도 단위로 끊어져서 회전하기 때문이 이 코드를 넣어서 부드럽게 회전을 보완.
		bUseControllerRotationYaw = false; //이거 왜 안먹지. 안먹는다. 엔진에티더에서 체크해제 해줘야돼.
		GetCharacterMovement()->bOrientRotationToMovement = false; //이거 없어도 된다. 이것도 안먹어.
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
	
	//6장 앞부분
	//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue); //이거 없으면 바인딩 해도 실제 캐릭터는 안움직여
	//AddMovementInput(GetActorForwardVector(), NewAxisValue); //이거 없으면 바인딩 해도 실제 캐릭터는 안움직여

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
	
	//6장 앞부분
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
	
	// 6장 앞부분
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
	
	// 6장 앞부분
	//AddControllerYawInput(NewAxisValue);
}
void AYHCharacter::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::GTA:
		//부드럽게 화면 전환하기 위해 추가한다.
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		//부드럽게 화면 전환하기 위해 추가한다.
		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		SetControlMode(EControlMode::GTA);
		break;
	}
}