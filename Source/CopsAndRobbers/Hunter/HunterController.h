#pragma once
#include "CoreMinimal.h"
#include "Player/PPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "HunterController.generated.h"

UCLASS()
class COPSANDROBBERS_API AHunterController : public APPlayerController
{
	GENERATED_BODY()
	
public:
	AHunterController();
protected:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxLife;
	UPROPERTY(VisibleInstanceOnly)
	int32 CurrentLife;
	virtual void BeginPlay() override;
public:

	int32 GetMaxLife() const { return MaxLife; };
	int32 GetCurrentLife() const { return CurrentLife; };

};
