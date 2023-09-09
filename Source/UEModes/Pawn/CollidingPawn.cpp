// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Hierarchy 2
	//1
	PlayerRootCollisionBox = CreateDefaultSubobject<UBoxComponent>("SceneRoot");
	//2
	PlayerRootCollisionBox->SetBoxExtent(FVector(100, 10, 100)); //100,10,100
	//3
	PlayerRootCollisionBox->SetSimulatePhysics(true);

	//UPhysicalMaterial* PhysicsMaterial = UPhysicalMaterial::CreatePhysicalMaterial(nullptr);
	//PhysicsMaterial->Friction = 1.0f;
	//PhysicsMaterial->Restitution = 0.0f;
	//PlayerRootCollisionBox->SetPhysMaterialOverride(PhysicsMaterial);

	//4 
	PlayerRootCollisionBox->SetCollisionProfileName("BlockAllDynamic");
	PlayerRootCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//5 - Add a Step and show camera . before 5
	PlayerRootCollisionBox->GetBodyInstance()->bLockRotation = true;// BodyInstance.bLockXRotation = true; SetConstraintMode(EDOFMode::XZPlane)
	PlayerRootCollisionBox->GetBodyInstance()->bLockXRotation = true;
	PlayerRootCollisionBox->GetBodyInstance()->bLockYRotation = true;
	PlayerRootCollisionBox->GetBodyInstance()->bLockZRotation = true;
	PlayerRootCollisionBox->GetBodyInstance()->bLockYTranslation = true;
	//6
	SetRootComponent(PlayerRootCollisionBox);

	//MISC
	PlayerRootCollisionBox->SetEnableGravity(false);
	
	//OR
	//RootComponent = PlayerRoot;
	PawnSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Pawn Sprite");
	PawnSpriteComponent->SetupAttachment(RootComponent);
	PawnSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
#pragma endregion Hierarchy 2	

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	NormalSpeed = 10;
	FastSpeed = 10;
	Speed = NormalSpeed;
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector NewLocation = GetActorLocation();
	//IF MovementForward NOT EQUAL to 0
	if (MovementUp != 0)
	{
	    //ASSIGN NewLocation to the the sum of the Actors Current Location and the product of the Actors Forward Vector and the MovementForward value i.e GetActorLocation() + (GetActorForwardVector() * MovementForward)
	    NewLocation = GetActorLocation() + (GetActorUpVector() * MovementUp * Speed);
	}
	//ENDIF	

	//CALL SetActorLocation() passing in NewLocation
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	
}

void ACollidingPawn::MoveUp(float value)
{
	MovementUp = value;

}

void ACollidingPawn::SpeedUp()
{
	Speed = FastSpeed;
}

void ACollidingPawn::SlowDown()
{
	Speed = NormalSpeed;
}

