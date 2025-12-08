#include "UI/LobbyUI.h"
#include "Player/PPlayerState.h"
#include "UI/PlayerEntryWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Player/LobbyPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameState.h"

void ULobbyUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (RenameEditableTextBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnTextCommittedRenameEditableTextBox) == false)
	{
		RenameEditableTextBox->OnTextCommitted.AddDynamic(this, &ThisClass::OnTextCommittedRenameEditableTextBox);
	}
	if (RenameButton->OnClicked.IsAlreadyBound(this, &ThisClass::OnClickedRenameButton) == false)
	{
		RenameButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedRenameButton);
	}
	if (StartButton->OnClicked.IsAlreadyBound(this, &ThisClass::OnClickedStartButton) == false)
	{
		StartButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedStartButton);
	}
}

void ULobbyUI::NativeDestruct()
{
	if (RenameEditableTextBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnTextCommittedRenameEditableTextBox) == true)
	{
		RenameEditableTextBox->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnTextCommittedRenameEditableTextBox);
	}
	if (RenameButton->OnClicked.IsAlreadyBound(this, &ThisClass::OnClickedRenameButton) == true)
	{
		RenameButton->OnClicked.RemoveDynamic(this, &ThisClass::OnClickedRenameButton);
	}
	if (StartButton->OnClicked.IsAlreadyBound(this, &ThisClass::OnClickedStartButton) == true)
	{
		StartButton->OnClicked.RemoveDynamic(this, &ThisClass::OnClickedStartButton);
	}

	Super::NativeDestruct();
}

void ULobbyUI::AddPlayerEntryWidget(APlayerState* InPlayerState)
{
	if (IsValid(PlayerEntryWidgetClass) == false) return;
	if (IsValid(InPlayerState) == false) return;

	APPlayerState* CastPlayerState = Cast<APPlayerState>(InPlayerState);
	if (IsValid(CastPlayerState) == false) return;

	UPlayerEntryWidget* PlayerEntryWidget = CreateWidget<UPlayerEntryWidget>(this, PlayerEntryWidgetClass);
	if (IsValid(PlayerEntryWidget) == false) return;

	const FName PlayerName = CastPlayerState->GetPlayerName();
	PlayerEntryWidget->GetPlayerNameTextBlock()->SetText(FText::FromName(PlayerName));
	
	PlayerEntryWidgets.Add(PlayerEntryWidget);
	PlayerListVerticalBox->AddChildToVerticalBox(PlayerEntryWidget);
}

void ULobbyUI::AddAllPlayerEntryWidgets()
{
	AGameStateBase* GameStateBase = GetWorld()->GetGameState();
	if (IsValid(GameStateBase) == false) return;

	for (APlayerState* PlayerState : GameStateBase->PlayerArray)
	{
		AddPlayerEntryWidget(PlayerState);
	}
}

void ULobbyUI::RemoveAllPlayerEntryWidgets()
{
	if (IsValid(PlayerListVerticalBox) == false) return;
	PlayerListVerticalBox->ClearChildren();
	PlayerEntryWidgets.Empty();
}

void ULobbyUI::OnTextCommittedRenameEditableTextBox(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod != ETextCommit::OnEnter) return;
	RenameEditableTextBox->SetText(FText::GetEmpty());
	const FName Newname = FName(Text.ToString());
	CommitRename(Newname);
}

void ULobbyUI::OnClickedRenameButton()
{
	const FName Newname = FName(RenameEditableTextBox->GetText().ToString());
	RenameEditableTextBox->SetText(FText::GetEmpty());
	CommitRename(Newname);
}

void ULobbyUI::OnClickedStartButton()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (IsValid(PlayerController) == false) return;

	ALobbyPlayerController* LobbyPlayerController = Cast<ALobbyPlayerController>(PlayerController);
	if (IsValid(LobbyPlayerController) == false) return;

	LobbyPlayerController->ServerRPCGameStartRequest();
}

void ULobbyUI::CommitRename(const FName& Newname)
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (IsValid(PlayerController) == false) return;
	
	ALobbyPlayerController* LobbyPlayerController = Cast<ALobbyPlayerController>(PlayerController);
	if (IsValid(LobbyPlayerController) == false) return;

	LobbyPlayerController->ServerRPCRenameCommitted(Newname);
}