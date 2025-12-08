#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class COPSANDROBBERS_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAICharacter();

protected:
	UPROPERTY(EditDefaultsOnly)
	float StandingWalkSpeed;

	virtual void BeginPlay() override;
public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
