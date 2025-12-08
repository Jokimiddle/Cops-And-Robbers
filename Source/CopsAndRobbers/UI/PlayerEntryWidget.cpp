#include "UI/PlayerEntryWidget.h"
#include "Components/Button.h"

void UPlayerEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BanButton->OnClicked.IsAlreadyBound(this, &ThisClass::OnClickedBanButton) == false)
	{
		BanButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedBanButton);
	}
}

void UPlayerEntryWidget::NativeDestruct()
{
	if (BanButton->OnClicked.IsAlreadyBound(this, &ThisClass::OnClickedBanButton) == false)
	{
		BanButton->OnClicked.RemoveDynamic(this, &ThisClass::OnClickedBanButton);
	}

	Super::NativeDestruct();
}

void UPlayerEntryWidget::OnClickedBanButton()
{
}
