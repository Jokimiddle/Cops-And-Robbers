#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInfo {
	GENERATED_BODY()
	TObjectPtr<APlayerController> PlayerController = nullptr;
	bool bAlive = false;
	FName PlayerName = FName();
};

UCLASS()
class COPSANDROBBERS_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FPlayerInfo> ValidPlayerList;
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	bool RequestChangePlayerName(APlayerController* InPlayerController, const FName& Newname);
	bool RequestGameStart(APlayerController* InPlayerController);
	void CreatePlayerEntryWidgets();
	void ChattingPrintLogic(APlayerController* InPlayerController, const FText& Text);
};
