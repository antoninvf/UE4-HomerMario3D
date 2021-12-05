// Fill out your copyright notice in the Description page of Project Settings.


#include "Homie.h"

#include "Components/CapsuleComponent.h"

// Sets default values
AHomie::AHomie()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Arm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	Score = 0;
}

// Called when the game starts or when spawned
void AHomie::BeginPlay()
{
	Super::BeginPlay();

	// Kontrola kolize CapsuleComponent
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHomie::OnCollide);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AHomie::OnStopCollision);
}

// Called every frame
void AHomie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, FString::Printf(TEXT("Score: %i"), Score), true);

}

// Called to bind functionality to input
void AHomie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AHomie::MoveForward);
	PlayerInputComponent->BindAxis("Sideways", this, &AHomie::MoveSideways);
	PlayerInputComponent->BindAxis("MouseMovementX", this, &AHomie::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseMovementY", this, &AHomie::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void AHomie::MoveForward(float Scale)
{
	AddMovementInput(GetActorForwardVector(), Scale);
}

void AHomie::MoveSideways(float Scale)
{
	AddMovementInput(GetActorRightVector(), Scale);
}

void AHomie::OnCollide(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Colliding with: %s"), *OtherActor->GetName());

	FString Actor = OtherActor->GetName().ToLower();

	if (Actor.Contains("cap"))
	{
		Score += 1;
		OtherActor->Destroy();
	}

	if (Actor.Contains("kill"))
	{
		FVector Location = GetActorLocation();
		Location.Set(0, 0, 0);
		SetActorLocation(Location);
	}
}

void AHomie::OnStopCollision(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                             class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// UE_LOG(LogTemp, Warning, TEXT("Collision stopped with: %s"), *OtherActor->GetFullName());
}
