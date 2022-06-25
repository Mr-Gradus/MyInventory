// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyInventoryGameMode.h"
#include "MyInventoryPlayerController.h"
#include "MyInventoryCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyInventoryGameMode::AMyInventoryGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMyInventoryPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}