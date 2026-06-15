// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "TopDownCameraManager.generated.h"

UCLASS()
class CRYPTDELVE_API ATopDownCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ATopDownCameraManager();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraHeight = 1200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraPitch = -60.f;

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
};
