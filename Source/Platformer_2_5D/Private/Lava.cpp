// Fill out your copyright notice in the Description page of Project Settings.


#include "Lava.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALava::ALava()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LavaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lava Mesh"));
	RootComponent = LavaMesh;

	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box"));
	DamageBox->SetupAttachment(RootComponent);
	DamageBox->SetCollisionProfileName("Trigger");
	DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ALava::OnOverlapBegain);

}

// Called when the game starts or when spawned
void ALava::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALava::OnOverlapBegain(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		ACharacter* Player = Cast<ACharacter>(OtherActor);
		if (Player)
		{
			UGameplayStatics::ApplyDamage(Player, 100.0f, nullptr, this, nullptr);
		}
	}
}

// Called every frame
void ALava::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

