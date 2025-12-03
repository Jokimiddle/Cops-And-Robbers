#include "Hunter/HunterController.h"

AHunterController::AHunterController()
{
	MaxLife = 3;
	CurrentLife = MaxLife;
}

void AHunterController::BeginPlay()
{
	Super::BeginPlay();
	CurrentLife = MaxLife;
}
