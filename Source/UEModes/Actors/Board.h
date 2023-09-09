#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Board.generated.h"

class AUEGameMode;
class AUEGameState;

UCLASS()
class UEMODES_API ABoard : public APaperSpriteActor
{
    GENERATED_BODY()

public:
    ABoard();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UCameraComponent* LevelCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UBoxComponent* UpBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UBoxComponent* BottomBox;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    //    class UBoxComponent* RightBox;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    //    class UBoxComponent* LeftBox;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Goal)
    //    AActor* MiddleOfField;

   /* UFUNCTION()
        void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/
};
