// Copyright Epic Games, Inc. All Rights Reserved.

#include "Platformer_2_5DGameMode.h"
#include "Platformer_2_5DCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatformer_2_5DGameMode::APlatformer_2_5DGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
