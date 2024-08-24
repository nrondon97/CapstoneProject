#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "../HiddingObjects.h"
#include "SightEnemy.h"
#include "../HearingEnemy.h"
#include "../EndGameTrigger.h"
#include "Engine/World.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class CAPSTONEPROJECT_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//variables
	bool IsPlayerHidden;
	bool HaveComfortObject;
	bool IsSneaking;
	float NoiseLevel;
	float AxisValueTracker;
	AHiddingObjects* CurrentHidingObject;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Setup Dying and Spawning Mechanic
	void Die();
	void Respawn();

protected:

	//Allows Character to Move forward and backwards
	void MoveRight(float AxisVal);

	// To Begin Sneaking
	void Sneak();

	// To Stop Sneaking
	void StopSneak();

	//Make the Character Noise
	void EmitNoise(float Loudness);
	void StopNoise();


	//Hiding Mechanic
	void Hide();
 


private:
	//Setting Up SideScroller Sytle Camera
	UPROPERTY(VisibleAnywhere, Category = Camera);
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, Category = Camera);
	class UCameraComponent* FollowCamera;


	//Setup Overlap for Hiding Objects
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox; // Collision box for overlap check

	//Proprty For Noise Emitter
	UPROPERTY(VisibleAnywhere)
	UPawnNoiseEmitterComponent* NoiseEmitter;


};
