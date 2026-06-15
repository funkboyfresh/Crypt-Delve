// Copyright CryptDelve. All Rights Reserved.

#include "Core/CryptDelveMenuGameMode.h"
#include "Core/CryptDelvePlayerController.h"

void ACryptDelveMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (ACryptDelvePlayerController* PC = Cast<ACryptDelvePlayerController>(It->Get()))
		{
			PC->ShowMainMenu();
		}
	}
}
