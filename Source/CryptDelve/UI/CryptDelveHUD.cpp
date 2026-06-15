// Copyright CryptDelve. All Rights Reserved.

#include "UI/CryptDelveHUD.h"
#include "UI/SkillTreeWidget.h"

void ACryptDelveHUD::BeginPlay()
{
	Super::BeginPlay();

	if (SkillTreeWidgetClass && GetOwningPlayerController())
	{
		SkillTreeWidget = CreateWidget<USkillTreeWidget>(GetOwningPlayerController(), SkillTreeWidgetClass);
		if (SkillTreeWidget)
		{
			SkillTreeWidget->AddToViewport(1);
		}
	}
}
