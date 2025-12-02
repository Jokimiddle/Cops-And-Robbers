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
	TObjectPtr<USceneComponent> SceneComponent;
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
	const float GetStandingWalkSpeed() const { return StandingWalkSpeed; };
	const float GetStandingRunSpeed() const { return StandingWalkSpeed * SprintSpeedScale; };
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
