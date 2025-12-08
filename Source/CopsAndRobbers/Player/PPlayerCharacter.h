#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
UCLASS()
class COPSANDROBBERS_API APPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APPlayerCharacter();

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	float StandingWalkSpeed;
	UPROPERTY(EditDefaultsOnly)
	float SprintSpeedScale;

	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Tick(float DeltaTime) override;
	
	const float GetStandingWalkSpeed() const { return StandingWalkSpeed; };
	const float GetStandingRunSpeed() const { return StandingWalkSpeed * SprintSpeedScale; };

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
