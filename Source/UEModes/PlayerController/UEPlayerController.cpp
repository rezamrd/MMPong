// Fill out your copyright notice in the Description page of Project Settings.


#include "UEPlayerController.h"
#include "UEModes/Pawn/CollidingPawn.h"
#include "UEModes/PlayerState/UEPlayerState.h"
#include "UEModes/Actors/Board.h"
#include "EngineUtils.h"

void AUEPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    MyPawn = Cast<ACollidingPawn>(aPawn);
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, "AMyPlayerController::Possess: - " + aPawn->GetName());
}

void AUEPlayerController::OnUnPossess()
{
    APawn* posessedPawn = Cast<APawn>(GetOwner());
    if (posessedPawn)
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow,"AMyPlayerController::UnPossess: - " + GetOwner()->GetName());

    Super::OnUnPossess();
}


void AUEPlayerController::BeginPlay() {
    Super::BeginPlay();
    AActor* MyBoard = nullptr;

    for (TActorIterator<ABoard> ActorItr(GetWorld()); ActorItr; ++ActorItr)

    {
        //CALL AddOnScreenDebugMessage() on GEngine passing in: -1, 15.0f, FColor::Green, "Actor: " + ActorItr->GetName()

        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Actor: " + ActorItr->GetName());
    
        if ((Cast<ABoard>(*ActorItr))) {

            MyBoard = *ActorItr;
            break;

        }
    }
    SetViewTarget(MyBoard);

}


void AUEPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    MyPlayerState = Cast<AUEPlayerState>(PlayerState);
    if (MyPlayerState)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found class %s"), TEXT("AMyPlayerController::BeginPlay: MyPlayerState Set"));
    }
    if (InputComponent != nullptr)
    {
        InputComponent->BindAxis("MoveUp", this, &AUEPlayerController::MoveUp);
        InputComponent->BindAction("Speed", IE_Pressed, this, &AUEPlayerController::SpeedUp);
        InputComponent->BindAction("Speed", IE_Released, this, &AUEPlayerController::SlowDown);
    }
}

void AUEPlayerController::AcknowledgePossession(APawn* PossesedPawn)
{

}

void AUEPlayerController::MoveUp(float value)
{
   
    if (MyPawn)
        MyPawn->MoveUp(value);
}

void AUEPlayerController::SpeedUp()
{
	if(MyPawn)
		MyPawn->SpeedUp();
}

void AUEPlayerController::SlowDown()
{
    if (MyPawn)
        MyPawn->SlowDown();
}
