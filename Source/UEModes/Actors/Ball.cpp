// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("SceneRoot");
	CollisionSphere->SetSphereRadius(24.0f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->SetCollisionProfileName("BlockAll");
	RootComponent = CollisionSphere;
	/**  paper sprite component */
	BallSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite Component"));
	BallSprite->SetupAttachment(RootComponent);
	BallSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BallMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BallMovementComponent"));
	BallMovementComponent->ProjectileGravityScale = 0.0f;
	BallMovementComponent->InitialSpeed = 1000;
	BallMovementComponent->MaxSpeed = 10000; 
	BallMovementComponent->bShouldBounce = true;
	BallMovementComponent->Bounciness = 1.1f;
	BallMovementComponent->Friction = 0.0;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	FVector location = GetActorLocation();
	location.Y = 0.0f;
	SetActorLocation(location);

	Super::Tick(DeltaTime);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), CollisionSphere->GetUnscaledSphereRadius(), 26, FColor::Green, true, -1, 0, 5);
}
void ABall::Destroyed()
{
	Super::Destroyed();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("BALL DESTROYED")));
}

UPrimitiveComponent* ABall::GetPhysicsComponent()
{
	return Cast<UPrimitiveComponent>(CollisionSphere);
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("%s has Hit"), *OtherActor->GetName()));
		}
	}
}

