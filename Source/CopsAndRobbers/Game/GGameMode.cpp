#include "Game/GGameMode.h"
#include "Game/LobbyGameMode.h"
#include "Game/GGameState.h"
#include "Player/PPlayerController.h"
#include "Player/PPlayerState.h"
#include "UI/ChattingWidget.h"

AGGameMode::AGGameMode()
{
	GameTimerRate = 1.0f;
}

void AGGameMode::BeginPlay()
{
	Super::BeginPlay();

	OnStartGameTimer();
}


void AGGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (IsValid(NewPlayer) == false) return;

	// 로그인 성공
	ValidPlayerList.Add({ NewPlayer, false, FName()});
}

void AGGameMode::OnStartGameTimer()
{
	AGGameState* CastGameState = GetGameState<AGGameState>();
	if (CastGameState == nullptr) return;
	
	CastGameState->SetCurrentGameTimer(CastGameState->GetMaxGameTimer() + GameTimerRate);
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ThisClass::OnGameTimerTick, GameTimerRate, true);
}

void AGGameMode::OnGameTimerTick()
{
	AGGameState* CastGameState = GetGameState<AGGameState>();
	if (CastGameState == nullptr) return;

	float CurrentGameTimer = CastGameState->GetCurrentGameTimer();
	const float MaxGameTimer = CastGameState->GetMaxGameTimer();
	CurrentGameTimer -= GameTimerRate;

	if (CurrentGameTimer <= 0.0f || FMath::IsNearlyZero(CurrentGameTimer) == true)
	{
		GetWorldTimerManager().ClearTimer(GameTimerHandle);
	}
	CastGameState->SetCurrentGameTimer(CurrentGameTimer);

	
	if (FMath::CeilToInt32(CurrentGameTimer) % 5 == 0)
	{
		FString LogMessage = FString::Printf(
			TEXT("[GameMode] GameTimer: %d / %d"), FMath::CeilToInt32(CurrentGameTimer), FMath::CeilToInt32(MaxGameTimer)
		);
		UE_LOG(LogTemp, Display, TEXT("%s"), *LogMessage);
	}
}

void AGGameMode::ChattingPrintLogic(APlayerController* InPlayerController, const FText& Text)
{
	if (IsValid(InPlayerController) == false) return;

	bool Found = false;
	FName SpeakerName = FName(TEXT("Unknown"));
	for (FPlayerInfo& PlayerInfo : ValidPlayerList)
	{
		if (PlayerInfo.PlayerController == InPlayerController)
		{
			SpeakerName = PlayerInfo.PlayerName;
			Found = true;
			break;
		}
	}

	for (FPlayerInfo& PlayerInfo : ValidPlayerList)
	{
		if (PlayerInfo.PlayerController == InPlayerController) continue;
		
		APPlayerState* CastPlayerState = PlayerInfo.PlayerController->GetPlayerState<APPlayerState>();
		if (IsValid(CastPlayerState) == false) continue;

		EChatType ChatType = EChatType::DefaultChat;
		CastPlayerState->ClientRPCChattingPrint(ChatType, SpeakerName, Text);
	}
}
