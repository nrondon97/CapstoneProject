#include "../Player/PlayableCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;

	//CameraSetup
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraArm ->SetupAttachment(GetMesh());
	CameraArm->TargetArmLength = 600.f;
	CameraArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayableCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &APlayableCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Sneak"), IE_Pressed, this, &APlayableCharacter::Sneak);
	PlayerInputComponent->BindAction(TEXT("Sneak"), IE_Released, this, &APlayableCharacter::StopSneak);
}

//Allow Character to Move Forward and Backwards
void APlayableCharacter::MoveRight(float AxisVal)
{
	AddMovementInput(GetActorForwardVector() * AxisVal);
}

//Sneaking Mechanic
void APlayableCharacter::Sneak()
{
	if (GetCharacterMovement()->MaxWalkSpeed == 200.f)
	{
		GetCharacterMovement()->MaxWalkSpeed *= 0.5;
	}
}

void APlayableCharacter::StopSneak()
{
	if (GetCharacterMovement()->MaxWalkSpeed < 200.f)
	{
		GetCharacterMovement()->MaxWalkSpeed = 200.f;
	}
}





