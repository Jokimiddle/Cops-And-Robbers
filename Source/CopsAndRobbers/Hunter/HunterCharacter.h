#pragma once
#include "CoreMinimal.h"
#include "Player/PPlayerCharacter.h"
#include "HunterCharacter.generated.h"

UCLASS()
class COPSANDROBBERS_API AHunterCharacter : public APPlayerCharacter
{
	GENERATED_BODY()

public:
	AHunterCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
