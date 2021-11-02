// Fill out your copyright notice in the Description page of Project Settings.


#include "YongHwan/FountainY.h"

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
}

// Called when the game starts or when spawned
void AFountainY::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFountainY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

