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
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite);
	FName PlayerName;
public:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	const FName GetPlayerName() const { return PlayerName; };
	void SetPlayerName(const FName& Newname) { PlayerName = Newname; };
	UFUNCTION(Server, Reliable)
	void ServerRPCChattingCommitted(APlayerController* InPlayerController, const FText& Text);
	UFUNCTION(Client, Reliable)
	void ClientRPCChattingPrint(const EChatType& InChatType, const FName& SpeakerName, const FText& Message);

	UFUNCTION(Client, Reliable)
	void ClientRPCCreatePlayerEntryWidget();

};
