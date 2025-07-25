// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lava.generated.h"

class UBoxComponent;

UCLASS()
class ALava : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALava();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	 
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LavaMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* DamageBox;

	UFUNCTION()
	void OnOverlapBegain(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
