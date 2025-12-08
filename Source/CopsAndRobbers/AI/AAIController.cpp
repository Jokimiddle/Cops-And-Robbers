#include "AI/AAIController.h"
#include "AI/AICharacter.h"
#include "NavigationSystem.h"
AAAIController::AAAIController()
{
	MoveRadius = 1000.0f;
}

void AAAIController::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(AIMoveTimerHandle, this, &ThisClass::MoveToRandomLocation, 5.0f, true);
}

void AAAIController::MoveToRandomLocation()
{
	ACharacter* TempCharacter = GetCharacter();
	if (IsValid(TempCharacter) == false) return;

	AAICharacter* AICharacter = Cast<AAICharacter>(TempCharacter);
	if (IsValid(AICharacter) == false) return;

	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (IsValid(NavigationSystem) == false) return;

	FNavLocation RandomLocation;

	bool bFoundLocation = NavigationSystem->GetRandomReachablePointInRadius(
		AICharacter->GetNavAgentLocation(), MoveRadius, RandomLocation);
	if (bFoundLocation == false) return;
	
	MoveToLocation(RandomLocation.Location);
}