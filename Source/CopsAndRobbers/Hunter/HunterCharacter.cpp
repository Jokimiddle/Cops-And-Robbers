#include "Hunter/HunterCharacter.h"
#include "GameFramework/SpringArmComponent.h"

AHunterCharacter::AHunterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponent->TargetArmLength = 0.0f;
}

void AHunterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasLocalNetOwner() == false) return;
}

void AHunterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHunterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

