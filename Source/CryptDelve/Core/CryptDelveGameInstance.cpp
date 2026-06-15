// Copyright CryptDelve. All Rights Reserved.

#include "Core/CryptDelveGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UCryptDelveGameInstance::TravelToMap(FName MapName)
{
	UGameplayStatics::OpenLevel(this, MapName);
}
