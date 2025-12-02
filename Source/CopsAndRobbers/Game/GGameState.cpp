#include "Game/GGameState.h"
#include "Net/UnrealNetwork.h"

AGGameState::AGGameState()
{
	MaxGameTimer = 30.0f;
	CurrentGameTimer = 0.0f;
}

void AGGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, MaxGameTimer);
	DOREPLIFETIME(ThisClass, CurrentGameTimer);
}

void AGGameState::OnRep_TimeValueChange()
{
	if (OnGameTimeChangeDelegate.IsBound())
	{
		OnGameTimeChangeDelegate.Broadcast(CurrentGameTimer, MaxGameTimer);
	}
}
