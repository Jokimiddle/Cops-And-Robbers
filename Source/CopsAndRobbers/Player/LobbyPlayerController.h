#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

class ULobbyUI;
class UChattingWidget;
UCLASS()
class COPSANDROBBERS_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALobbyPlayerController();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<ULobbyUI> LobbyUIClass;
	UPROPERTY(VisibleInstanceOnly, Category = "Widgets")
	TObjectPtr<ULobbyUI> LobbyUI;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UChattingWidget> ChattingWidgetClass;
	UPROPERTY(VisibleInstanceOnly, Category = "Widgets")
	TObjectPtr<UChattingWidget> ChattingWidget;
	virtual void BeginPlay() override;
public:
	UFUNCTION(Server, Reliable)
	void ServerRPCRenameCommitted(const FName& Newname);
	UFUNCTION(Server, Reliable)
	void ServerRPCCreatePlayerEntryWidgets();
	UFUNCTION(Server, Reliable)
	void ServerRPCGameStartRequest();
	ULobbyUI* GetLobbyUI() const { return LobbyUI; };
	UChattingWidget* GetChattingWidget() const { return ChattingWidget; };

};
