// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerCollision.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "UEModes/Actors/Ball.h"
#include "UEModes/GameMode/UEGameMode.h"
#include "UEModes/GameState/UEGameState.h"
#include "UEModes/PlayerState/UEPlayerState.h"
#include "UEModes/Spawner/ActorSpawner.h"

// Sets default values
ATriggerCollision::ATriggerCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//1
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("SceneRoot");
	//2
	TriggerBox->SetBoxExtent(FVector(120, 50, 140)); //100,10,100
	//3
	TriggerBox->SetSimulatePhysics(false);
	//4 - Add a Step and show camera .
	TriggerBox->SetCollisionProfileName("OverlapAllDynamic");
	//5	
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//6
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerCollision::BeginOverlap);
	//TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATriggerCollision::EndOverlap);
	
	SetRootComponent(TriggerBox);

}

//void ATriggerCollision::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor && OtherActor != this)
//	{
//		if (GEngine)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Begin"));
//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Overlapping Actor = %s"), *OtherActor->GetName()));
//		}
//
//		//WEEK 7
//		//ABall* ball = Cast<ABall>(OtherActor);
//		if(OtherActor->IsA<ABall>())
//		{
//			//CALL TeleportTo() on OtherActor passing in MiddleOfField->GetActorLocation(), FRotator::ZeroRotator
//			//OtherActor->TeleportTo(MiddleOfField->GetActorLocation(), FRotator::ZeroRotator);
//
//			//DECLARE a temporary variable called gameMode of type AUEGameMode* and assign it to the return value of Cast<AUEGameMode>( GetWorld()->GetAuthGameMode() )
//			AUEGameMode* gameMode = Cast<AUEGameMode>(GetWorld()->GetAuthGameMode());
//
//			//DECLARE a temporary variable called gameState of type AUEGameState* and assign it to the return value of  gameMode->GetGameState<AUEGameState>()
//			AUEGameState* gameState = gameMode->GetGameState<AUEGameState>();
//
//			//DECLARE a temporary variable called playerState of type AUEPlayerState* and assign it to the return value of   Cast<AUEPlayerState>( gameState->PlayerArray[0] )
//			
//			//INCREMENT NumberOfGoals property on playerState
//			
//			//IF goal IS EGoal::LEFT
//			if (goal == EGoal::LEFT)
//			{
//				gameState->NumberOfRightGoals++;
//			}
//			else 
//			{
//				gameState->NumberOfLeftGoals++;
//			}
//			   //INCREMENT 	NumberOfLeftGoals property on gameState
//			
//			//ELSE
//			
//				//INCREMENT NumberOfRightGoals property on gameState
//			//ENDIF
//			OtherActor->Destroy();
//		}
//	}
//		UWorld* World = GetWorld();
//		//IF World is NOT EQUAL to nullptr
//		if (World)
//		{
//	     	FActorSpawnParameters SpawnParams;
//			
//			SpawnParams.Owner = this;
//			
//			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//			FTransform SpawnTransform = SpawnPointComponent->GetComponentTransform();
//
//			ABall* SpawnedActor = World->SpawnActor<ABall>(BallTemplate, SpawnTransform, SpawnParams);
//
//			if (SpawnedActor)
//			{
//				FVector direction = FRotationMatrix(SpawnTransform.Rotator()).GetScaledAxis(EAxis::X);
//	
//				UPrimitiveComponent* physicsComponent = SpawnedActor->GetPhysicsComponent();
//
//				physicsComponent->AddForce(direction * 1000000, NAME_None, true);
//			}
//		}
//	}


void ATriggerCollision::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Begin"));
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Overlapping Actor = %s"), *OtherActor->GetName()));
		}

		if (OtherActor->IsA<ABall>())
		{
			AUEGameMode* gameMode = Cast<AUEGameMode>(GetWorld()->GetAuthGameMode());
			AUEGameState* gameState = gameMode->GetGameState<AUEGameState>();
			AUEPlayerState* playerState = Cast<AUEPlayerState>(gameState->PlayerArray[0]);

			if (goal == EGoal::LEFT)
			{
				gameState->NumberOfRightGoals++;
			}
			else
			{
				gameState->NumberOfLeftGoals++;
			}

			OtherActor->Destroy();

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FVector spawnLocation = MiddleOfField->GetActorLocation();
				FRotator spawnRotation = MiddleOfField->GetActorRotation();

				World->SpawnActor(BallTemplate, &spawnLocation, &spawnRotation);
				
			}
		}
	}
}

// Called when the game starts or when spawned
void ATriggerCollision::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), GetActorLocation(), TriggerBox->GetUnscaledBoxExtent(), FColor::Green, true, 999, 0, 5);
}

// Called every frame
void ATriggerCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

