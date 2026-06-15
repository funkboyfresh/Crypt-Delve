// Copyright CryptDelve. All Rights Reserved.

#include "Progression/SkillTreeComponent.h"
#include "Progression/SkillTreeDefinition.h"
#include "Characters/CharacterProfileComponent.h"
#include "Abilities/CryptDelveAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

USkillTreeComponent::USkillTreeComponent()
{
	SetIsReplicatedByDefault(true);
}

void USkillTreeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USkillTreeComponent, UnlockedNodeIds);
	DOREPLIFETIME(USkillTreeComponent, AvailablePoints);
}

bool USkillTreeComponent::CanUnlockNode(FName NodeId) const
{
	const FSkillTreeNode* Node = FindNode(NodeId);
	if (!Node || UnlockedNodeIds.Contains(NodeId))
	{
		return false;
	}

	if (AvailablePoints < Node->PointCost)
	{
		return false;
	}

	return HasPrerequisites(*Node);
}

bool USkillTreeComponent::UnlockNode(FName NodeId)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		Server_UnlockNode(NodeId);
		return false;
	}

	if (!CanUnlockNode(NodeId))
	{
		return false;
	}

	const FSkillTreeNode* Node = FindNode(NodeId);
	if (!Node)
	{
		return false;
	}

	AvailablePoints -= Node->PointCost;
	UnlockedNodeIds.Add(NodeId);

	if (UCharacterProfileComponent* ProfileComp = GetOwner()->FindComponentByClass<UCharacterProfileComponent>())
	{
		FCharacterProfile Profile = ProfileComp->GetProfile();
		Profile.UnlockedSkillNodeIds = UnlockedNodeIds;
		Profile.UnspentSkillPoints = AvailablePoints;
		ProfileComp->SetProfile(Profile);
	}

	OnSkillUnlocked.Broadcast(NodeId);
	return true;
}

void USkillTreeComponent::Server_UnlockNode_Implementation(FName NodeId)
{
	UnlockNode(NodeId);
}

const FSkillTreeNode* USkillTreeComponent::FindNode(FName NodeId) const
{
	if (!SkillTree)
	{
		return nullptr;
	}

	for (const FSkillTreeNode& Node : SkillTree->Nodes)
	{
		if (Node.NodeId == NodeId)
		{
			return &Node;
		}
	}
	return nullptr;
}

bool USkillTreeComponent::HasPrerequisites(const FSkillTreeNode& Node) const
{
	for (const FName& Prereq : Node.PrerequisiteNodeIds)
	{
		if (!UnlockedNodeIds.Contains(Prereq))
		{
			return false;
		}
	}
	return true;
}

void USkillTreeComponent::OnRep_UnlockedNodes()
{
	OnSkillUnlocked.Broadcast(NAME_None);
}
