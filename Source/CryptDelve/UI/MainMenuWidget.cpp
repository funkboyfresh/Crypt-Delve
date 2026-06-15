// Copyright CryptDelve. All Rights Reserved.

#include "UI/MainMenuWidget.h"
#include "Core/CryptDelveGameInstance.h"
#include "Core/CryptDelvePlayerController.h"
#include "Network/CryptDelveNetworkSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainMenuWidget::OnLoginClicked()
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCryptDelveNetworkSubsystem* Net = GI->GetSubsystem<UCryptDelveNetworkSubsystem>())
		{
			Net->Login();
		}

		if (UCryptDelveGameInstance* CDGI = Cast<UCryptDelveGameInstance>(GI))
		{
			CDGI->SetFlowState(ECryptDelveFlowState::Login);
		}
	}

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ACryptDelvePlayerController* CDPC = Cast<ACryptDelvePlayerController>(PC))
		{
			DeactivateWidget();
			CDPC->ShowCharacterSelect();
		}
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
