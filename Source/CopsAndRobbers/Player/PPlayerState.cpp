#include "Player/PPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameMode.h"
#include "Game/GGameMode.h"

APPlayerState::APPlayerState()
{
	PlayerName = FName(TEXT("Unknown"));
	bReplicates = true;
}

void APPlayerState::ServerRPCChattingCommitted_Implementation(APlayerController* InPlayerController, const FText& Text)
{
	if (IsValid(InPlayerController) == false) return;

	AGameModeBase* GmaeModeBase = UGameplayStatics::GetGameMode(this);
	if (GmaeModeBase == nullptr) return;	// not server

	AGameMode* GmaeMode = Cast<AGameMode>(GmaeModeBase);
	if (GmaeMode == nullptr) return;

	AGGameMode* CastGmaeMode = Cast<AGGameMode>(GmaeMode);
	if (CastGmaeMode == nullptr) return;

	CastGmaeMode->ClientRPCChattingPrint(InPlayerController, Text);
}
