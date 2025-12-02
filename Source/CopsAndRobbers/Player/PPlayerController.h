#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

class APPlayerCharacter;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UStatusWidget;
class UChattingWidget;
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
	UPROPERTY(EditDefaultsOnly, Category = "InputAction|Inputs")
	TObjectPtr<UInputAction> ChatAction;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStatusWidget> StatusWidgetClass;
	UPROPERTY(VisibleInstanceOnly, Category = "Widgets")
	TObjectPtr<UStatusWidget> StatusWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UChattingWidget> ChattingWidgetClass;
	UPROPERTY(VisibleInstanceOnly, Category = "Widgets")
	TObjectPtr<UChattingWidget> ChattingWidget;

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
	UFUNCTION()
	void HandleChatInput(const FInputActionValue& InValue);

	UStatusWidget* GetStatusWidget() const { return StatusWidget; };
	UChattingWidget* GetChattingWidget() const { return ChattingWidget; };

};
