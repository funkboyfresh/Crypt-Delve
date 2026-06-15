// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CryptDelveHUD.generated.h"

UCLASS()
class CRYPTDELVE_API ACryptDelveHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class USkillTreeWidget> SkillTreeWidgetClass;

	UPROPERTY()
	TObjectPtr<class USkillTreeWidget> SkillTreeWidget;
};
