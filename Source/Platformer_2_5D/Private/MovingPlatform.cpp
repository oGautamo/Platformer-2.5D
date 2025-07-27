// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	RootComponent = PlatformMesh;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	TargetLocation = GetActorLocation() + FVector(MoveDistance, 0.f, 0.f);

	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	
	FVector MoveDirection = bMovingToTarget ? (TargetLocation - StartLocation).GetSafeNormal() : (StartLocation - TargetLocation).GetSafeNormal();

	// Move Platform
	CurrentLocation += MoveDirection * MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);

	// Check if we've reached (or passed) the destination
	float DistanceTravel = FVector::Dist(StartLocation, CurrentLocation);

	if (DistanceTravel >= MoveDistance)
	{
		// Swap direction
		bMovingToTarget = !bMovingToTarget;

		// Snap to endpoint to avoid overshooting
		SetActorLocation(bMovingToTarget ? StartLocation : TargetLocation);
	}


}

