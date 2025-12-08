#include "Game/LobbyGameMode.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Player/PPlayerState.h"
#include "UI/ChattingWidget.h"
#include "Player/PPlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (IsValid(NewPlayer) == false) return;

	// 로그인 성공
	FName Name = FName(FString("Client") + FString::FromInt(ValidPlayerList.Num()));
	if (APlayerState* TempPlayerState = NewPlayer->PlayerState)
	{
		APPlayerState* CastPlayerState = Cast<APPlayerState>(TempPlayerState);
		CastPlayerState->SetPlayerName(Name);
		ValidPlayerList.Add({ NewPlayer, false, CastPlayerState->GetPlayerName()});
	}
	else
	{
		NewPlayer->ClientTravel(TEXT(""), ETravelType::TRAVEL_Absolute);
	}
}

bool ALobbyGameMode::RequestChangePlayerName(APlayerController* InPlayerController, const FName& Newname)
{
	bool bIsDuplicate = false;
	for (FPlayerInfo& PlayerInfo : ValidPlayerList)
	{
		if (PlayerInfo.PlayerName.ToString() == Newname.ToString())
		{
			bIsDuplicate = true;
			break;
		}
	}
	if (bIsDuplicate == false)		// 중복된 이름이 검출되지 않음
	{
		for (FPlayerInfo& PlayerInfo : ValidPlayerList)
		{
			if (PlayerInfo.PlayerController == InPlayerController)
			{
				if (APlayerState* TempPlayerState = PlayerInfo.PlayerController->PlayerState)
				{
					APPlayerState* CastPlayerState = Cast<APPlayerState>(TempPlayerState);
					if (IsValid(CastPlayerState) == false) continue;

					PlayerInfo.PlayerName = Newname;
					CastPlayerState->SetPlayerName(PlayerInfo.PlayerName);

					return true;
				}
			}
		}
	}
	return false;	// 중복된 이름 검출 또는 변경실패
}

bool ALobbyGameMode::RequestGameStart(APlayerController* InPlayerController)
{
	if (ValidPlayerList.Num() <= 0) return false;
	if (ValidPlayerList[0].PlayerController == InPlayerController)
	{
		GetWorld()->ServerTravel(TEXT("/Game/CopsAndRobbers/Maps/TestMap"));
		return true;
	}
	return false;
}

void ALobbyGameMode::CreatePlayerEntryWidgets()
{
	for (FPlayerInfo& PlayerInfo : ValidPlayerList)
	{
		APlayerState* TempPlayerState = PlayerInfo.PlayerController->PlayerState;
		if (IsValid(TempPlayerState) == false) return;

		APPlayerState* CastPlayerState = Cast<APPlayerState>(TempPlayerState);
		if (IsValid(CastPlayerState) == false) return;
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *CastPlayerState->GetPlayerName().ToString());
		CastPlayerState->ClientRPCCreatePlayerEntryWidget();
	}
}

void ALobbyGameMode::ChattingPrintLogic(APlayerController* InPlayerController, const FText& Text)
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
