// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/CryptDelveGameMode.h"
#include "CryptDelveZoneGameMode.generated.h"

UCLASS()
class CRYPTDELVE_API ACryptDelveZoneGameMode : public ACryptDelveGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
