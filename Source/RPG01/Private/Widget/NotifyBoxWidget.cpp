// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NotifyBoxWidget.h"
#include "Widget/NotifyWidget.h"
#include "DataAsset/RarityData.h"
#include "Components/VerticalBox.h"

UNotifyBoxWidget* UNotifyBoxWidget::Instance = nullptr;

UNotifyBoxWidget* UNotifyBoxWidget::Get()
{
	return Instance;
}

void UNotifyBoxWidget::InitInstance(APlayerController* PlayerController, TSubclassOf<UNotifyBoxWidget> NotifyBoxWidgetClass)
{
	Instance = CreateWidget<UNotifyBoxWidget>(PlayerController, NotifyBoxWidgetClass);
}

void UNotifyBoxWidget::AddNotify(const FItemInfomation& ItemInfo, TSubclassOf<UNotifyWidget> NotifyWidgetClass)
{
	if (NotifyBox) 
	{
		auto NotifyWidget = CreateWidget<UNotifyWidget>(GetOwningPlayer(), NotifyWidgetClass);
		NotifyBox->AddChild(NotifyWidget);

		GEngine->AddOnScreenDebugMessage(
			-1,
			3.0f,
			FColor::White,
			TEXT("Add Child Notify Box")
		);

		if (RarityData)
		{
			NotifyWidget->SetupData(RarityData->GetRarityBGIcon(ItemInfo.Rarity), ItemInfo.Icon, ItemInfo.ItemName.ToString(), ItemInfo.Stack);
			NotifyWidget->ShowNotify();
		}
	}

}
