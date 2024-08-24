#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 
#include "../CapstoneProject/Player/PlayableCharacter.h"
#include "Components/BoxComponent.h"
#include "ComfortObjective.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AComfortObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values
	AComfortObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//To create overlap events
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


	//Creating Collision Box for Character to interact with
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionBox;

};
