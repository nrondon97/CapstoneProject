#include "../Player/PlayableCharacter.h"
#include "../ComfortObjective.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Walking Speed
	GetCharacterMovement()->MaxWalkSpeed = 200.f;

	//Variables
	IsPlayerHidden = false;
	HaveComfortObject = false;
	CurrentHidingObject = nullptr;
	NoiseLevel = 1.0f;

	//Collison
	// Create and set up the collision box 
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f)); // Set the size
	CollisionBox->SetCollisionProfileName("Trigger"); 

	// Bind overlap events
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayableCharacter::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &APlayableCharacter::OnOverlapEnd);

	//CameraSetup
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraArm ->SetupAttachment(GetMesh());
	CameraArm->TargetArmLength = 600.f;
	CameraArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Noise Emitter
	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));

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

	//Make noise only when walking
	if (GetVelocity().Size() > 0.0f && NoiseLevel > 0.0f)
	{
		EmitNoise(NoiseLevel);  // Sound Level for normal movement
		UE_LOG(LogTemp, Warning, TEXT("Character is Moving"));
	}

}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayableCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &APlayableCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Sneak"), IE_Pressed, this, &APlayableCharacter::Sneak);
	PlayerInputComponent->BindAction(TEXT("Sneak"), IE_Released, this, &APlayableCharacter::StopSneak);

	PlayerInputComponent->BindAction(TEXT("Hide"), IE_Pressed, this, &APlayableCharacter::Hide);
}

void APlayableCharacter::Die()
{
	//Add a Death Screen

	UE_LOG(LogTemp, Warning, TEXT("Character has died"));
	//Call Respawn
	this->Respawn();
}

void APlayableCharacter::Respawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Level Restart"));
	//Restart Game
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
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
		GetCharacterMovement()->MaxWalkSpeed *= 0.5; //Slow the character down
		if (NoiseLevel > 0.0f)
		{
			NoiseLevel = 0.0f;  // Reduce noise when sneaking
			UE_LOG(LogTemp, Warning, TEXT("Character is Not Making Noise"));
		}
	}
}

void APlayableCharacter::StopSneak()
{
	if (GetCharacterMovement()->MaxWalkSpeed < 200.f)
	{
		GetCharacterMovement()->MaxWalkSpeed = 200.f; //Return to normal speed
		if (NoiseLevel == 0.0f)
		{
			NoiseLevel = 1.0f;  // Increase noise when stopping sneak
			UE_LOG(LogTemp, Warning, TEXT("Character is Making Noise"));
		}
	}
}

void APlayableCharacter::EmitNoise(float Loudness)
{
		if (NoiseEmitter)
		{
			NoiseEmitter->MakeNoise(this, Loudness, GetActorLocation());
			UE_LOG(LogTemp, Warning, TEXT("Character is Making Noise"));
		}
}


//Hiding Function
void APlayableCharacter::Hide()
{
	
	if (!IsPlayerHidden)
	{
		if (CurrentHidingObject) // Ensure the character is overlapping with a hiding object
		{
			IsPlayerHidden = true;
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			GetCharacterMovement()->DisableMovement(); //Disable movement
			NoiseLevel = 0.0f;  // Reduce noise when hidden
			UE_LOG(LogTemp, Log, TEXT("Character is now hidden. IsPlayerHidden: %s, Collision: %s, MovementMode: %d"),
				IsPlayerHidden ? TEXT("true") : TEXT("false"),
				GetActorEnableCollision() ? TEXT("true") : TEXT("false"),
				GetCharacterMovement()->MovementMode);
		}
		
	}
	else
	{
		IsPlayerHidden = false;
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking); //Enable Movement
		NoiseLevel = 1.0f;  // Return to normal status
		UE_LOG(LogTemp, Log, TEXT("Character is now unhidden. IsPlayerHidden: %s, Collision: %s, MovementMode: %d"),
			IsPlayerHidden ? TEXT("true") : TEXT("false"),
			GetActorEnableCollision() ? TEXT("true") : TEXT("false"),
			GetCharacterMovement()->MovementMode);
	}


}

//Interacting with Anything 
void APlayableCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping object is a hiding object
	AHiddingObjects* HiddingObject = Cast<AHiddingObjects>(OtherActor);
	if (HiddingObject)
	{
		CurrentHidingObject = HiddingObject;
	}
	//Check if the overlapping Object is an enemy
	ASightEnemy* SightEnemy = Cast<ASightEnemy>(OtherActor);
	if (SightEnemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping with SightEnemy"));
		this->Die();
	}
	//Check if the overlapping Object is an enemy
	AHearingEnemy* HearingEnemy = Cast<AHearingEnemy>(OtherActor);
	if (HearingEnemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping with HearingEnemy"));
		this->Die();
	}
	//Check if overlap with the ComfortObject
	AComfortObjective* ComfortObjective = Cast<AComfortObjective>(OtherActor);
	if (ComfortObjective)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping with Comfort Objective"));
		HaveComfortObject = true;
	}

	//Check if overlap with the EngGameTrigger
	AEndGameTrigger* EndGameTrigger = Cast<AEndGameTrigger>(OtherActor);
	if (ComfortObjective)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping with trigger"));
		if (HaveComfortObject) //Check if have the comfort objective
		{

			UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuMap"));
		}
	}
}

void APlayableCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == CurrentHidingObject)
	{
		CurrentHidingObject = nullptr;
	}
}





