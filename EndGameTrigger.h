#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndGameTrigger.generated.h"

UCLASS()
class CAPSTONEPROJECT_API AEndGameTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndGameTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Creating Collision Box for Character to interact with
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionBox;

};
