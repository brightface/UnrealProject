// Fill out your copyright notice in the Description page of Project Settings.

#include "../../UnrealProject.h" 
#include "YongHwan/FountainY.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
AFountainY::AFountainY()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("YBODY"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("YWATER"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("YLIGHT"));
	Splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("YSPLASH"));

	RootComponent = Body;
	Water->SetupAttachment(Body);
	Light->SetupAttachment(Body);
	Splash->SetupAttachment(Body);
	
	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f));
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));
	Splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));

	//이걸로 에셋 경로 불러온후
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_BODY(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	
	//이걸로 할수있다.
	if (SM_BODY.Succeeded())
	{
		
		Body->SetStaticMesh(SM_BODY.Object);
	}

	//이걸로 에셋 경로 불러온후
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_YWATER(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Meshes/Env/SM_Plains_Fountain_02.SM_Plains_Fountain_02"));

	//이걸로 할수있다.
	if (SM_YWATER.Succeeded())
	{
		//에셋로딩
		Body->SetStaticMesh(SM_YWATER.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		PS_SPLASH(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_01.P_Water_Fountain_Splash_01"));

	//이걸로 할수있다.
	if (PS_SPLASH.Succeeded())
	{
		//에셋로딩
		Splash->SetTemplate(PS_SPLASH.Object);
	}
	RotateSpeed = 30.0f;
}

// Called when the game starts or when spawned
void AFountainY::BeginPlay()
{
	Super::BeginPlay();
	YHLOG_S(Warning);
	YHLOG(Warning, TEXT("Actor Name : %s, ID : %d, Location X:%.3f"), *GetName(), ID, GetActorLocation().X);
}

void AFountainY::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Super::EndPlay(EEndPlayReason);
	YHLOG_S(Warning);
}

void AFountainY::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	YHLOG_S(Warning);
}



// Called every frame
void AFountainY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, RotateSpeed * DeltaTime, 0.0f));
}

