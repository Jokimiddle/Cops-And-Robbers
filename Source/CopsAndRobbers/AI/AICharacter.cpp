#include "AI/AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

AAICharacter::AAICharacter()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; // AI 자동 빙의
	
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	StandingWalkSpeed = 300.0f;
	GetCharacterMovement()->MaxWalkSpeed = StandingWalkSpeed;
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

