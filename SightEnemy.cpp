
#include "../Player/SightEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ASightEnemy::ASightEnemy()
{
 	// Set this character to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = 350.f; //Make the enemy slightly faster than the player

}

// Called when the game starts or when spawned
void ASightEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASightEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASightEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


