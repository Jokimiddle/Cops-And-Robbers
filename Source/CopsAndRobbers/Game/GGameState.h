#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameTimeChange, float, CurrentTime, float, MaxTime);

UCLASS()
class COPSANDROBBERS_API AGGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AGGameState();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_TimeValueChange, EditDefaultsOnly)
	float MaxGameTimer;
	UPROPERTY(ReplicatedUsing = OnRep_TimeValueChange, EditDefaultsOnly)
	float CurrentGameTimer;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameTimeChange OnGameTimeChangeDelegate;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	const float GetMaxGameTimer() const { return MaxGameTimer; };
	const float GetCurrentGameTimer() const { return CurrentGameTimer; };

	void SetCurrentGameTimer(float value) { CurrentGameTimer = value; };

	UFUNCTION()
	void OnRep_TimeValueChange();
};
