#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

class UGridPanel;
class UTextBlock;

UCLASS()
class COPSANDROBBERS_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UStatusWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UGridPanel> TimeGrid;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeValue;

public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnGameTimeChange(float CurrentTime, float MaxTime);
};
