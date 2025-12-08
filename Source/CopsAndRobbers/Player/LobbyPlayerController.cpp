#include "Player/LobbyPlayerController.h"
#include "UI/LobbyUI.h"
#include "UI/ChattingWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game/LobbyGameMode.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	bReplicates = true;
	LobbyUIClass = nullptr;
	ChattingWidgetClass = nullptr;
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController() == false) return;

	if (IsValid(LobbyUIClass) == true)
	{
		LobbyUI = CreateWidget<ULobbyUI>(this, LobbyUIClass);
		if (IsValid(LobbyUI))
		{
			LobbyUI->AddToViewport();
			LobbyUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			ServerRPCCreatePlayerEntryWidgets();
		}
	}
	if (IsValid(ChattingWidgetClass) == true)
	{
		ChattingWidget = CreateWidget<UChattingWidget>(this, ChattingWidgetClass);
		if (IsValid(ChattingWidget))
		{
			ChattingWidget->AddToViewport();
			ChattingWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}

void ALobbyPlayerController::ServerRPCCreatePlayerEntryWidgets_Implementation()
{
	if (HasAuthority() == false) return;

	AGameModeBase* GmaeModeBase = UGameplayStatics::GetGameMode(this);
	if (IsValid(GmaeModeBase) == false) return;	// not server

	AGameMode* GmaeMode = Cast<AGameMode>(GmaeModeBase);
	if (IsValid(GmaeMode) == false) return;

	ALobbyGameMode* CastGameMode = Cast<ALobbyGameMode>(GmaeMode);
	if (IsValid(CastGameMode) == false) return;

	CastGameMode->CreatePlayerEntryWidgets();
}

void ALobbyPlayerController::ServerRPCGameStartRequest_Implementation()
{
	if (HasAuthority() == false) return;

	AGameModeBase* GmaeModeBase = UGameplayStatics::GetGameMode(this);
	if (IsValid(GmaeModeBase) == false) return;	// not server

	AGameMode* GmaeMode = Cast<AGameMode>(GmaeModeBase);
	if (IsValid(GmaeMode) == false) return;

	ALobbyGameMode* CastGameMode = Cast<ALobbyGameMode>(GmaeMode);
	if (IsValid(CastGameMode) == false) return;

	CastGameMode->RequestGameStart(this);
}

void ALobbyPlayerController::ServerRPCRenameCommitted_Implementation(const FName& Newname)
{
	if (Newname.IsNone()) return;

	AGameModeBase* GmaeModeBase = UGameplayStatics::GetGameMode(this);
	if (IsValid(GmaeModeBase) == false) return;	// not server

	AGameMode* GmaeMode = Cast<AGameMode>(GmaeModeBase);
	if (IsValid(GmaeMode) == false) return;

	ALobbyGameMode* CastGmaeMode = Cast<ALobbyGameMode>(GmaeMode);
	if (IsValid(CastGmaeMode) == false) return;

	bool IsChanged = CastGmaeMode->RequestChangePlayerName(this, Newname);
	if (IsChanged)
	{
		CastGmaeMode->CreatePlayerEntryWidgets();
	}
}
