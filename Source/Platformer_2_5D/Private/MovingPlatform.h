// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveDistance = 500.0f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlatformMesh;

private:
	FVector StartLocation;
	FVector TargetLocation;
	bool bMovingToTarget = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
