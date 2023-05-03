// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnknownGameMode.h"
#include "UnknownCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnknownGameMode::AUnknownGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
