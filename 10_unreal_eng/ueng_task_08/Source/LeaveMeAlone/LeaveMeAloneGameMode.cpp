// Copyright Epic Games, Inc. All Rights Reserved.

#include "LeaveMeAloneGameMode.h"
#include "LeaveMeAloneCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALeaveMeAloneGameMode::ALeaveMeAloneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
