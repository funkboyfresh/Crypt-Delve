// Copyright CryptDelve. All Rights Reserved.

#include "UI/SkillTreeWidget.h"
#include "Core/CryptDelveCharacter.h"
#include "Progression/SkillTreeComponent.h"

void USkillTreeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillTreeWidget::RequestUnlockNode(FName NodeId)
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ACryptDelveCharacter* Character = Cast<ACryptDelveCharacter>(PC->GetPawn()))
		{
			if (USkillTreeComponent* SkillTree = Character->GetSkillTreeComponent())
			{
				SkillTree->UnlockNode(NodeId);
			}
		}
	}
}
