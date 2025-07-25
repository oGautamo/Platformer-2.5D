// Fill out your copyright notice in the Description page of Project Settings.


#include "Charactor.h"
#include "InputActionValue.h"
#include "GameFramework/Actor.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "Kismet/GameplayStatics.h"


// Sets default values
ACharactor::ACharactor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharactor::BeginPlay()
{
	Super::BeginPlay();

	// Lock movement to X/Z (side-scroller plane)
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f)); // Locks to X/Z by disallowing Y

	// Set default walk speed 
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Set default Health
	CurrentrHealth = MaxHealth;

	APlayerController* MouseyController = Cast<APlayerController>(GetController());
	if (MouseyController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MouseyController->GetLocalPlayer());
			
			if (Subsystem) {
				Subsystem->AddMappingContext(MouseyContext, 0);

			}
	}

	
}


float ACharactor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentrHealth -= DamageAmount;

	if (CurrentrHealth <= 0.0f) {
		Die();
	}
	return DamageAmount;
}

void ACharactor::Die()
{
	// Stop input + disable collisions 
	DisableInput(nullptr);
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Simulate physics on the mesh (ragdoll)
	if (GetMesh())
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	}

}

// Called every frame
void ACharactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void ACharactor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Moving
		EnhancedInputComponent -> BindAction(MovementAction, ETriggerEvent::Triggered, this, &ACharactor::MoveForward);

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ACharactor::StartSprinting);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACharactor::StopSprinting);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! "), *GetNameSafe(this));
	}
}




void ACharactor::MoveForward(const FInputActionValue& Value)
{
	const float MovementValue = Value.Get<float>();

	if (MovementValue && (Controller != 0.f)) {

		const FRotator ControlRot = Controller->GetControlRotation();
		const FRotator YawRotation(0, ControlRot.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, MovementValue);
	}

}

void ACharactor::StartSprinting(const FInputActionValue& Value)
{
	
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Started Sprinting"));
	
}

void ACharactor::StopSprinting(const FInputActionValue& Value)
{
	
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Stopped Sprinting"));
	

}
