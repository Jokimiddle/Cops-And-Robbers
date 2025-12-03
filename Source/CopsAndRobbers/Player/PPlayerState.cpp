#include "Player/PPlayerState.h"
#include "Player/PPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameMode.h"
#include "Game/GGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UI/ChattingWidget.h"

APPlayerState::APPlayerState()
{
	bReplicates = true;
	PlayerName = FName(TEXT("Unknown"));
}

void APPlayerState::BeginPlay()
{
	Super::BeginPlay();
}


void APPlayerState::ServerRPCChattingCommitted_Implementation(APlayerController* InPlayerController, const FText& Text)
{
	if (IsValid(InPlayerController) == false) return;

	AGameModeBase* GmaeModeBase = UGameplayStatics::GetGameMode(this);
	if (IsValid(GmaeModeBase) == false) return;	// not server

	AGameMode* GmaeMode = Cast<AGameMode>(GmaeModeBase);
	if (IsValid(GmaeMode) == false) return;

	AGGameMode* CastGmaeMode = Cast<AGGameMode>(GmaeMode);
	if (IsValid(CastGmaeMode) == false) return;

	CastGmaeMode->ChattingPrintLogic(InPlayerController, Text);
}


void APPlayerState::ClientRPCChattingPrint_Implementation(const EChatType& InChatType, const FText& SpeakerName, const FText& Message)
{
	APlayerController* PlayerController = GetPlayerController();
	if (IsValid(PlayerController) == false) return;

	APPlayerController* CastPlayerController = Cast<APPlayerController>(PlayerController);
	if (IsValid(CastPlayerController) == false) return;

	UChattingWidget* ChattingWidget = CastPlayerController->GetChattingWidget();
	if (IsValid(ChattingWidget) == false) return;

	ChattingWidget->ReceiveChatMessage(InChatType, SpeakerName, Message);
}