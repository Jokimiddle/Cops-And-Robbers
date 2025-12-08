#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "AAIController.generated.h"

UCLASS()
class COPSANDROBBERS_API AAAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAAIController();
protected:
	UPROPERTY(EditDefaultsOnly)
	float MoveRadius;
public:
	FTimerHandle AIMoveTimerHandle;
	virtual void BeginPlay() override;
	void MoveToRandomLocation();
};
