#include "UI/StatusWidget.h"
#include "Components/TextBlock.h"
#include "Game/GGameState.h"

UStatusWidget::UStatusWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UStatusWidget::NativeConstruct()
{
	AGGameState* CastGameState = GetWorld()->GetGameState<AGGameState>();
	if(CastGameState)
	{
		CastGameState->OnGameTimeChangeDelegate.AddDynamic(
			this,
			&ThisClass::OnGameTimeChange
		);
	}
}

void UStatusWidget::OnGameTimeChange(float CurrentTime, float MaxTime)
{
	FString TimeString = FString::Printf(
		TEXT("%d / %d"), FMath::CeilToInt32(CurrentTime), FMath::CeilToInt32(MaxTime)
	);

	TimeValue->SetText(FText::FromString(TimeString));
}
