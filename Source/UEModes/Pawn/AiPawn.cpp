// Fill out your copyright notice in the Description page of Project Settings.


#include "UEModes/Pawn/AiPawn.h"
#include <Perception/AIPerceptionComponent.h>
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include <UEModes/Actors/Ball.h>
#include <Kismet/GameplayStatics.h>

AAiPawn::AAiPawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AiCollisionBox = CreateDefaultSubobject<UBoxComponent>("SceneRoot");
	AiCollisionBox->SetBoxExtent(FVector(100, 10, 100));
	AiCollisionBox->SetSimulatePhysics(true);
	AiCollisionBox->SetCollisionProfileName("BlockAllDynamic");
	AiCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	AiCollisionBox->GetBodyInstance()->bLockRotation = true;// BodyInstance.bLockXRotation = true; SetConstraintMode(EDOFMode::XZPlane)
	AiCollisionBox->GetBodyInstance()->bLockXRotation = true;
	AiCollisionBox->GetBodyInstance()->bLockYRotation = true;
	AiCollisionBox->GetBodyInstance()->bLockZRotation = true;
	AiCollisionBox->GetBodyInstance()->bLockYTranslation = true;

	SetRootComponent(AiCollisionBox);

	AiCollisionBox->SetEnableGravity(false);

	AiSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite Component"));
	AiSprite->SetupAttachment(RootComponent);
	AiSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAiPawn::BeginPlay()
{
	Super::BeginPlay();
	if (!Ball)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyPaddle is missing reference to the ball"));
	}
	GetWorldTimerManager().SetTimer(SearchBallTimerHandle, this, &AAiPawn::SearchForBall, SearchBallDelay, true);
}

void AAiPawn::SearchForBall()
{
	// Check if the ball exists in the world
	Ball = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass()));

	// Ball found, stop the timer and proceed with AI logic
	if (Ball && Ball->IsValidLowLevel())
	{
		GetWorldTimerManager().ClearTimer(SearchBallTimerHandle);
	}
}

void AAiPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Search for the ball dynamically in each tick
	Ball = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass()));

	if (Ball && Ball->IsValidLowLevel())
	{
		FVector CurrentLocation = GetActorLocation();
		FVector CurrentBallLocation = Ball->GetActorLocation();

		float Intensity = FMath::Sign(CurrentBallLocation.Z - CurrentLocation.Z);
		Move(Intensity);
	}
}


void AAiPawn::Move(float Direction)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Z += Speed * Direction;
	SetActorLocation(CurrentLocation);
}