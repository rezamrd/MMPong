#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class UEMODES_API ACollidingPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ACollidingPawn();

    UPROPERTY(EditAnywhere, Category = "Pawn Visual")
        class UPaperSpriteComponent* PawnSpriteComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
        class UBoxComponent* PlayerRootCollisionBox;

    float Speed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Speed")
        float NormalSpeed;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Speed")
        float FastSpeed;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
        class UArrowComponent* SpawnPointComponent;

    UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        FTimerHandle SpawnTimer;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveUp(float value);

    void SpeedUp();
    void SlowDown();

private:
    float MovementUp;
};
