// Copyright CryptDelve. All Rights Reserved.

#include "Core/TopDownCameraManager.h"

ATopDownCameraManager::ATopDownCameraManager()
{
}

void ATopDownCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);

	if (AActor* Target = OutVT.Target)
	{
		const FVector TargetLocation = Target->GetActorLocation();
		OutVT.POV.Location = TargetLocation + FVector(0.f, 0.f, CameraHeight);
		OutVT.POV.Rotation = FRotator(CameraPitch, OutVT.POV.Rotation.Yaw, 0.f);
	}
}
