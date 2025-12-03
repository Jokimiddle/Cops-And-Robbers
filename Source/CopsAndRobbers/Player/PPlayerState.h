#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PPlayerState.generated.h"

enum class EChatType : uint8;
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
	virtual void BeginPlay() override;
	const FName GetPlayerName() const { return PlayerName; };

	UFUNCTION(Server, Reliable)
	void ServerRPCChattingCommitted(APlayerController* InPlayerController, const FText& Text);
	UFUNCTION(Client, Reliable)
	void ClientRPCChattingPrint(const EChatType& InChatType, const FText& SpeakerName, const FText& Message);

};
