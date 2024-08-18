#include "EndGameTrigger.h"

// Sets default values
AEndGameTrigger::AEndGameTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEndGameTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndGameTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

