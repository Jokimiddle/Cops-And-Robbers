#include "Player/PPlayerController.h"
#include "Player/PPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/StatusWidget.h"
#include "UI/ChattingWidget.h"
#include "Blueprint/UserWidget.h"

// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("My Debug Message!"));
APPlayerController::APPlayerController()
{
	PlayerCharacter = nullptr;

	InputMappingContext = nullptr;
	LookAction = nullptr;
	MoveAction = nullptr;
	JumpAction = nullptr;
	SprintAction = nullptr;
	ChatAction = nullptr;

	StatusWidgetClass = nullptr;
	StatusWidget = nullptr;

	ChattingWidgetClass = nullptr;
	ChattingWidget = nullptr;
}

void APPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == true)
	{
		UEnhancedInputLocalPlayerSubsystem* EILPS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (EILPS == nullptr) return;

		EILPS->AddMappingContext(InputMappingContext, 0);

		if (IsValid(StatusWidgetClass) == true)
		{
			StatusWidget = CreateWidget<UStatusWidget>(this, StatusWidgetClass);
			if (IsValid(StatusWidget))
			{
				StatusWidget->AddToViewport();
				StatusWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
		}

		if (IsValid(ChattingWidgetClass) == true)
		{
			ChattingWidget = CreateWidget<UChattingWidget>(this, ChattingWidgetClass);
			if (IsValid(ChattingWidget))
			{
				ChattingWidget->AddToViewport();
				ChattingWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				//ChattingWidget->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}

	if (ACharacter* CastCharacter = GetPawn<ACharacter>())
	{
		PlayerCharacter = Cast<APPlayerCharacter>(CastCharacter);
	}
}

void APPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsValid(InputMappingContext) == false) return;
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	if (IsValid(LookAction) == true)
	{
		EnhancedInputComponent->BindAction(
			LookAction, 
			ETriggerEvent::Triggered, 
			this, 
			&ThisClass::HandleLookInput
		);
	}

	if (IsValid(MoveAction) == true)
	{
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			this,
			&ThisClass::HandleMoveInput
		);
	}

	if (IsValid(JumpAction) == true)
	{
		EnhancedInputComponent->BindAction(
			JumpAction,
			ETriggerEvent::Triggered,
			this,
			&ThisClass::HandleJumpInputStart
		);
		EnhancedInputComponent->BindAction(
			JumpAction,
			ETriggerEvent::Completed,
			this,
			&ThisClass::HandleJumpInputEnd
		);
	}

	if (IsValid(SprintAction) == true)
	{
		EnhancedInputComponent->BindAction(
			SprintAction,
			ETriggerEvent::Triggered,
			this,
			&ThisClass::HandleSprintInputStart
		);
		EnhancedInputComponent->BindAction(
			SprintAction,
			ETriggerEvent::Completed,
			this,
			&ThisClass::HandleSprintInputEnd
		);
	}

	if (IsValid(ChatAction) == true)
	{
		EnhancedInputComponent->BindAction(
			ChatAction,
			ETriggerEvent::Triggered,
			this,
			&ThisClass::HandleChatInput
		);
	}
}

void APPlayerController::HandleLookInput(const FInputActionValue& InValue)
{
	FVector2D Look2DVector = InValue.Get<FVector2D>();
	AddYawInput(Look2DVector.X);
	AddPitchInput(Look2DVector.Y);
}

void APPlayerController::HandleMoveInput(const FInputActionValue& InValue)
{
	FVector2D Move2DVector = InValue.Get<FVector2D>();
	const FRotator MoveRotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(MoveRotator).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(MoveRotator).GetUnitAxis(EAxis::Y);

	if (FMath::IsNearlyZero(Move2DVector.X) == false)
	{
		GetPawn()->AddMovementInput(ForwardDirection, Move2DVector.X);
	}
	if (FMath::IsNearlyZero(Move2DVector.Y) == false)
	{
		GetPawn()->AddMovementInput(RightDirection, Move2DVector.Y);
	}
}

void APPlayerController::HandleJumpInputStart(const FInputActionValue& InValue)
{
	if (IsValid(PlayerCharacter) == false) return;
	PlayerCharacter->Jump();
}

void APPlayerController::HandleJumpInputEnd(const FInputActionValue& InValue)
{
	if (IsValid(PlayerCharacter) == false) return;
	PlayerCharacter->StopJumping();
}

void APPlayerController::HandleSprintInputStart(const FInputActionValue& InValue)
{
	if (IsValid(PlayerCharacter) == false) return;
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetStandingRunSpeed();
}

void APPlayerController::HandleSprintInputEnd(const FInputActionValue& InValue)
{
	if (IsValid(PlayerCharacter) == false) return;
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetStandingWalkSpeed();
}

void APPlayerController::HandleChatInput(const FInputActionValue& InValue)
{
	if (IsValid(ChattingWidget) == false) return;
	ChattingWidget->ChattingInputReady();
}
