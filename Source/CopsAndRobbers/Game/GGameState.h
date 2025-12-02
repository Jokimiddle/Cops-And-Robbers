#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GGameState.generated.h"

UCLASS()
class COPSANDROBBERS_API AGGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AGGameState();

protected:
	UPROPERTY(EditDefaultsOnly)
	float MaxGameTimer;
	UPROPERTY(EditDefaultsOnly)
	float CurrentGameTimer;
public:
};
