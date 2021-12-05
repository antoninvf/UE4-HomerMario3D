// Fill out your copyright notice in the Description page of Project Settings.


#include "Cap.h"

// Sets default values
ACap::ACap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
}

// Called when the game starts or when spawned
void ACap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator Rotator = GetActorRotation();
	Rotator.Yaw += 3;
	SetActorRotation(Rotator);

}