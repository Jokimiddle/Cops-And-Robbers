#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

class APPlayerCharacter;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class COPSANDROBBERS_API APPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APPlayerController();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character|Player")
	TObjectPtr<APPlayerCharacter> PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "InputMappingContext|Inputs")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "InputAction|Inputs")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "InputAction|Inputs")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "InputAction|Inputs")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "InputAction|Inputs")
	TObjectPtr<UInputAction> SprintAction;


	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
public:
	UFUNCTION()
	void HandleLookInput(const FInputActionValue& InValue);
	UFUNCTION()
	void HandleMoveInput(const FInputActionValue& InValue);
	UFUNCTION()
	void HandleJumpInputStart(const FInputActionValue& InValue);
	UFUNCTION()
	void HandleJumpInputEnd(const FInputActionValue& InValue);
	UFUNCTION()
	void HandleSprintInputStart(const FInputActionValue& InValue);
	UFUNCTION()
	void HandleSprintInputEnd(const FInputActionValue& InValue);
};
