#include "UI/ChattingWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Player/PPlayerState.h"

void UChattingWidget::NativeConstruct()
{
	
	Super::NativeConstruct();

	if (ChattingInputBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChattingCommitted) == false)
	{
		ChattingInputBox->OnTextCommitted.AddDynamic(this, &ThisClass::OnChattingCommitted);
	}
	ChattingInputBox->ClearKeyboardFocusOnCommit = false;
}

void UChattingWidget::NativeDestruct()
{
	if (ChattingInputBox->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChattingCommitted) == true)
	{
		ChattingInputBox->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChattingCommitted);
	}
	Super::NativeDestruct();
}

void UChattingWidget::OnChattingCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod != ETextCommit::OnEnter) return;
	if (Text.IsEmpty())
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		return;
	}

	APPlayerState* CastPlayerState = GetOwningPlayerState<APPlayerState>();
	if (CastPlayerState == nullptr) return;

	FText MyName = FText::FromName(CastPlayerState->GetPlayerName());
	EChatType ChatType = EChatType::DefaultChat;
	
	ReceiveChatMessage(ChatType, MyName, Text);
	CastPlayerState->ServerRPCChattingCommitted(GetOwningPlayer(), Text);
	
	ChattingInputBox->SetText(FText::GetEmpty());	// 채팅 비우기
	// OnChattingCommitted 함수가 종료되면 Focus 해제 로직이 실행됨
	// Focus 해제로직이 마지막으로 덮어씌워지기 때문에 다음 Tick에 실행하여 로직을
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::ChattingInputReady);
	
}

void UChattingWidget::ChattingInputReady()
{
	ChattingInputBox->SetUserFocus(GetOwningPlayer());
	FSlateApplication::Get().SetKeyboardFocus(ChattingInputBox->TakeWidget());
}

void UChattingWidget::ReceiveChatMessage(EChatType& InChatType, const FText& SpeakerName, const FText& Message)
{
	FText PrintMessage;
	switch (InChatType)
	{
	case EChatType::System:
		break;
	case EChatType::DefaultChat:
		PrintMessage = FText::FromString(
			SpeakerName.ToString() + TEXT(": ") + Message.ToString()
		);
		break;
	}
	UTextBlock* ChattingTextBlock = NewObject<UTextBlock>(GetOwningPlayer());
	if (ChattingTextBlock == nullptr) return;

	ChattingTextBlock->SetText(PrintMessage);
	UVerticalBoxSlot* TextSlot = ChattingVerticalBox->AddChildToVerticalBox(ChattingTextBlock);
}