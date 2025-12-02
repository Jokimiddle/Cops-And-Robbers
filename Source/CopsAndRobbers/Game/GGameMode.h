#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GGameMode.generated.h"

class APPlayerController;

UCLASS()
class COPSANDROBBERS_API AGGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AGGameMode();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<APPlayerController>> ValidPlayerList;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<APPlayerController>> AlivePlayerList;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<APPlayerController>> DeadPlayerList;
public:
};
