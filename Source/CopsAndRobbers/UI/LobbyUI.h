#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUI.generated.h"

class UVerticalBox;
class UEditableTextBox;
class UButton;
class UPlayerEntryWidget;

UCLASS()
class COPSANDROBBERS_API ULobbyUI : public UUserWidget
{
	GENERATED_BODY()

public:
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> PlayerListVerticalBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> RenameEditableTextBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RenameButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UPlayerEntryWidget> PlayerEntryWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerList")
	TArray<TObjectPtr<UPlayerEntryWidget>> PlayerEntryWidgets;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	TArray<TObjectPtr<UPlayerEntryWidget>>* GetPlayerEntryWidgets() { return &PlayerEntryWidgets; };

	void AddPlayerEntryWidget(APlayerState* InPlayerState);
	void AddAllPlayerEntryWidgets();
	void RemoveAllPlayerEntryWidgets();

	UFUNCTION()
	void OnTextCommittedRenameEditableTextBox(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnClickedRenameButton();
	UFUNCTION()
	void OnClickedStartButton();
	void CommitRename(const FName& Newname);

};
