#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GGameMode.generated.h"

struct FPlayerInfo;

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

	void ChattingPrintLogic(APlayerController* InPlayerController, const FText& Text);
};
