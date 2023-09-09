#include "UEModes/Actors/Board.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "UEModes/Actors/Ball.h"
#include "UEModes/GameMode/UEGameMode.h"
#include "UEModes/GameState/UEGameState.h"
#include "UEModes/PlayerState/UEPlayerState.h"
#include "EngineUtils.h" 
#include "UEModes/Pawn/CollidingPawn.h"

ABoard::ABoard()
{
    PrimaryActorTick.bCanEverTick = true;

    SetRootComponent(GetRenderComponent());

    UpBox = CreateDefaultSubobject<UBoxComponent>("UpBox");
    UpBox->SetupAttachment(RootComponent);
    UpBox->SetBoxExtent(FVector(1200.0f, 800.0f, 100.0f));

    UpBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    UpBox->SetCollisionProfileName("BlockAll");
    UpBox->SetRelativeLocation(FVector(0.0f, 0.0f, 670.0f));

    BottomBox = CreateDefaultSubobject<UBoxComponent>("BottomBox");
    BottomBox->SetupAttachment(RootComponent);
    BottomBox->SetBoxExtent(FVector(1200.0f, 500.0f, 100.0f));

    BottomBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BottomBox->SetCollisionProfileName("BlockAll");
    BottomBox->SetRelativeLocation(FVector(0.0f, 0.0f, -670.0f));

    //LeftBox = CreateDefaultSubobject<UBoxComponent>("LeftBox");
    //LeftBox->SetupAttachment(RootComponent);
    //LeftBox->SetBoxExtent(FVector(100.0f, 800.0f, 1200.0f));

    //LeftBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //LeftBox->SetCollisionProfileName("OverlapAll");
    //LeftBox->SetRelativeLocation(FVector(-1200.0f, 0.0f, -670.0f));

    //// Add dynamic delegate for LeftBox
    //LeftBox->OnComponentBeginOverlap.AddDynamic(this, &ABoard::BeginOverlap);

    //RightBox = CreateDefaultSubobject<UBoxComponent>("RightBox");
    //RightBox->SetupAttachment(RootComponent);
    //RightBox->SetBoxExtent(FVector(100.0f, 800.0f, 1200.0f));

    //RightBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //RightBox->SetCollisionProfileName("OverlapAll");
    //RightBox->SetRelativeLocation(FVector(1200.0f, 0.0f, 0.0f));

    //// Add dynamic delegate for RightBox
    //RightBox->OnComponentBeginOverlap.AddDynamic(this, &ABoard::BeginOverlap);

    LevelCamera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    LevelCamera->SetupAttachment(RootComponent);
    LevelCamera->SetRelativeLocation(FVector(0.0f, 1300.0f, 0.0f));
    LevelCamera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

//void ABoard::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
//		if (OtherActor->IsA<ABall>())
//		{
//			//CALL TeleportTo() on OtherActor passing in MiddleOfField->GetActorLocation(), FRotator::ZeroRotator
//			OtherActor->TeleportTo(MiddleOfField->GetActorLocation(), FRotator::ZeroRotator);
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
//			if (OverlappedComponent == RightBox)
//			{
//				gameState->NumberOfLeftGoals++;
//			}
//			else if (OverlappedComponent == LeftBox)
//			{
//				gameState->NumberOfRightGoals++;
//			}
//
//			
//
//		}
//	}
// 
//    OtherActor->Destroy();
//}







