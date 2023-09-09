#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "UEModes/Actors/Ball.h"
#include "AiPawn.generated.h"

UCLASS()
class UEMODES_API AAiPawn : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAiPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		class UBoxComponent* AiCollisionBox;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Actor Visual")
		class UPaperSpriteComponent* AiSprite;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		float Speed = 20;

	UPROPERTY(EditAnywhere)
		ABall* Ball = nullptr;

	void Move(float Direction);

	FTimerHandle SearchBallTimerHandle;
	float SearchBallDelay = 0.5f;

	void SearchForBall();
};
