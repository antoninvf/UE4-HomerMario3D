// Fill out your copyright notice in the Description page of Project Settings.


#include "MovePlatform.h"

// Sets default values
AMovePlatform::AMovePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	Direction = 1;
}

// Called when the game starts or when spawned
void AMovePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActorLocation = GetActorLocation();
	
	if(ActorLocation.X > 1314)
	{
		Direction *= -1;
	}
	if(ActorLocation.X < 494)
	{
		Direction *= -1;
	}

	ActorLocation.X += Direction * 2;
	
	SetActorLocation(ActorLocation);

}

