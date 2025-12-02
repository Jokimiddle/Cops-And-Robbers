#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChattingWidget.generated.h"

class UEditableTextBox;
class UVerticalBox;

UENUM(BlueprintType)
enum class EChatType : uint8
{
	None,
	DefaultChat,
	System,
	End
};

UCLASS()
class COPSANDROBBERS_API UChattingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> ChattingInputBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ChattingVerticalBox;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnChattingCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	void ChattingInputReady();

	void ReceiveChatMessage(EChatType& InChatType, const FText& SpeakerName, const FText& Message);
};
