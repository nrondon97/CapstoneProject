#include "ComfortObjective.h"

// Sets default values
AComfortObjective::AComfortObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collison
	// Create and set up the collision box 
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(90.0f, 90.0f, 90.0f)); // Set the size
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RootComponent = CollisionBox;


	// Bind overlap events
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AComfortObjective::OnOverlapBegin);

}

// Called when the game starts or when spawned 
void AComfortObjective::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AComfortObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Overlap Player and Object
void AComfortObjective::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor is valid: %s"), *OtherActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor is NULL"));
	}


	APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(OtherActor);
	if (PlayableCharacter)
	{
		// Log to confirm overlap
		UE_LOG(LogTemp, Warning, TEXT("Player has reached the Comfort Objective"));

		// Hide the mesh and disable collisions
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor is not a PlayableCharacter"));
	}
}



