#include "Player/PPlayerState.h"
#include "Player/PPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameMode.h"
#include "Game/GGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UI/ChattingWidget.h"
#include "UI/LobbyUI.h"
#include "Game/LobbyGameMode.h"
#include "Player/LobbyPlayerController.h"
#include "Net/UnrealNetwork.h"

APPlayerState::APPlayerState()
{
	bReplicates = true;
	PlayerName = FName(TEXT("Unknown"));
}

void APPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void APPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(ThisClass, PlayerName);
}

void APPlayerState::ServerRPCChattingCommitted_Implementation(APlayerController* InPlayerController, const FText& Text)
{
	if (IsValid(InPlayerController) == false) return;

	AGameModeBase* GmaeModeBase = UGameplayStatics::GetGameMode(this);
	if (IsValid(GmaeModeBase) == false) return;	// not server

	AGameMode* GmaeMode = Cast<AGameMode>(GmaeModeBase);
	if (IsValid(GmaeMode) == false) return;

	if (AGGameMode* CastGameMode = Cast<AGGameMode>(GmaeMode))
	{
		CastGameMode->ChattingPrintLogic(InPlayerController, Text);
	}
	else if (ALobbyGameMode* CastGameMode2 = Cast<ALobbyGameMode>(GmaeMode))
	{
		CastGameMode2->ChattingPrintLogic(InPlayerController, Text);
	}
}

void APPlayerState::ClientRPCChattingPrint_Implementation(const EChatType& InChatType, const FName& SpeakerName, const FText& Message)
{
	APlayerController* PlayerController = GetPlayerController();
	if (IsValid(PlayerController) == false) return;

	UChattingWidget* ChattingWidget = nullptr;
	if (APPlayerController* CastPlayerController = Cast<APPlayerController>(PlayerController))
	{
		ChattingWidget = CastPlayerController->GetChattingWidget();
	}
	else if (ALobbyPlayerController* CastPlayerController2 = Cast<ALobbyPlayerController>(PlayerController))
	{
		ChattingWidget = CastPlayerController2->GetChattingWidget();
	}

	if (IsValid(ChattingWidget) == false) return;
	ChattingWidget->ReceiveChatMessage(InChatType, SpeakerName, Message);
}

void APPlayerState::ClientRPCCreatePlayerEntryWidget_Implementation()
{
	APlayerController* PlayerController = GetPlayerController();
	if (IsValid(PlayerController) == false) return;

	ALobbyPlayerController* CastPlayerController = Cast<ALobbyPlayerController>(PlayerController);
	if (IsValid(CastPlayerController) == false) return;

	ULobbyUI* LobbyUI = CastPlayerController->GetLobbyUI();
	if (IsValid(LobbyUI) == false) return;

	LobbyUI->RemoveAllPlayerEntryWidgets();
	LobbyUI->AddAllPlayerEntryWidgets();
}