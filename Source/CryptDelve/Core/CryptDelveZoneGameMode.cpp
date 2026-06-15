// Copyright CryptDelve. All Rights Reserved.

#include "Core/CryptDelveZoneGameMode.h"

void ACryptDelveZoneGameMode::BeginPlay()
{
	Super::BeginPlay();
	BeginRun(FName(TEXT("CryptOfAsh")), FMath::Rand());
}
