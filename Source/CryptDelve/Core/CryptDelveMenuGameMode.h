// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/CryptDelveGameMode.h"
#include "CryptDelveMenuGameMode.generated.h"

UCLASS()
class CRYPTDELVE_API ACryptDelveMenuGameMode : public ACryptDelveGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
