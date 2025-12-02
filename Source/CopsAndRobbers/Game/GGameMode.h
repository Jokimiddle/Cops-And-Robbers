#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GGameMode.generated.h"

class APPlayerController;
//UENUM(BlueprintType)
//enum class EStatus : uint8
//{
//	None,
//	Alive,
//	Dead,
//	End
//};
USTRUCT(BlueprintType)
struct FPlayerInfo {
	GENERATED_BODY()
	TObjectPtr<APPlayerController> PlayerController = nullptr;
	bool bAlive = false;
	FText PlayerName = FText::GetEmpty();
};

UCLASS()
class COPSANDROBBERS_API AGGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AGGameMode();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FPlayerInfo> ValidPlayerList;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)

	float GameTimerRate;
	virtual void BeginPlay() override;
public:
	FTimerHandle GameTimerHandle;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	void OnStartGameTimer();
	UFUNCTION()
	void OnGameTimerTick();

	UFUNCTION(Client, Reliable)
	void ClientRPCChattingPrint(APlayerController* InPlayerController, const FText& Text);
};
