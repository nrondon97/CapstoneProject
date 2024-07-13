#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//Allows Character to Move forward and backwards
	void MoveRight(float AxisVal);

private:
	//Setting Up SideScroller Sytle Camera
	UPROPERTY(VisibleAnywhere, Category = Camera);
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, Category = Camera);
	class UCameraComponent* FollowCamera;


};
