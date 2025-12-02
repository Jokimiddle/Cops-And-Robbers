#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PPlayerState.generated.h"

UCLASS()
class COPSANDROBBERS_API APPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	APPlayerState();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	FName PlayerName;
public:
	const FName GetPlayerName() const { return PlayerName; };
	
	UFUNCTION(Server, Reliable)
	void ServerRPCChattingCommitted(APlayerController* InPlayerController, const FText& Text);
};
