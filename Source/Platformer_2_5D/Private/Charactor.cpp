// Fill out your copyright notice in the Description page of Project Settings.


#include "Charactor.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


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

	APlayerController* MouseyController = Cast<APlayerController>(GetController());
	if (MouseyController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MouseyController->GetLocalPlayer());
			
			if (Subsystem) {
				Subsystem->AddMappingContext(MouseyContext, 0);

			}
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

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
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
