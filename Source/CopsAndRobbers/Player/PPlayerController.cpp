#include "Player/PPlayerController.h"
#include "Player/PPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("My Debug Message!"));
APPlayerController::APPlayerController()
{
	PlayerCharacter = nullptr;

	InputMappingContext = nullptr;
	LookAction = nullptr;
	MoveAction = nullptr;
	JumpAction = nullptr;
	SprintAction = nullptr;
}

void APPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == true)
	{
		UEnhancedInputLocalPlayerSubsystem* EILPS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (EILPS == nullptr) return;

		EILPS->AddMappingContext(InputMappingContext, 0);
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("My Debug Message!"));

}

void APPlayerController::HandleSprintInputEnd(const FInputActionValue& InValue)
{
	if (IsValid(PlayerCharacter) == false) return;
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetStandingWalkSpeed();
}
