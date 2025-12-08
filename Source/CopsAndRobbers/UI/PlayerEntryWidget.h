#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEntryWidget.generated.h"

class UTextBlock;
class UButton;
UCLASS()
class COPSANDROBBERS_API UPlayerEntryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameTextBlock;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BanButton;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UTextBlock* GetPlayerNameTextBlock() const { return PlayerNameTextBlock; };
	
	UFUNCTION()
	void OnClickedBanButton();
};
