// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EquipmentSlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Widget/InventoryWidget.h"
#include "Widget/TooltipWidget.h"
#include "DataAsset/InventorySystemData.h"
#include "DataAsset/RarityData.h"
#include "Component/InventorySystemComponent.h"
#include "Interface/InventoryInterface.h"



bool UEquipmentSlotWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UEquipmentSlotWidget::OnClickedItemIcon);
	}

	if (GetOwningPlayer())
	{
		InventoryInterface = TScriptInterface<IInventoryInterface>(GetOwningPlayer()->GetPawn());
	}

	if (InventoryInterface)
	{
		InventorySystem = InventoryInterface->GetInventorySystem();
	}

	if (InventorySystem)
	{
		auto ItemInfoRef = InventorySystem->AttachedEquipment.Find(EquipmentSlotIndex);
		if (ItemInfoRef && ItemInfoRef->ItemClass)
		{
			ItemInfo = *ItemInfoRef;
		}
	}

	UpdateWidget();

	return true;
}

void UEquipmentSlotWidget::UpdateWidget()
{
	if (!InventorySystem) return;
	if (!InventorySystem->InventorySystemData || !InventorySystem->RarityData) return;

	if (ItemIcon)
	{
		if (ItemInfo.ItemClass)
		{
			ItemIcon->SetBrushResourceObject(ItemInfo.Icon);
			ItemIcon->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (ItemButton)
	{
		FButtonStyle ButtonStyle = FButtonStyle();
		
		auto NormalSlateBrush = FSlateBrush();
		NormalSlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
		NormalSlateBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
		
		NormalSlateBrush.OutlineSettings.CornerRadii = FVector4(10, 10, 10, 10);
		NormalSlateBrush.OutlineSettings.Width = 4.0f;

		if (ItemInfo.ItemClass)
		{
			//Tooltip Widget
			auto TooltipWidget = CreateWidget<UTooltipWidget>(GetOwningPlayer(), InventorySystem->InventorySystemData->TooltipWidgetClass);
			TooltipWidget->ItemInfo = ItemInfo;
			TooltipWidget->CurrentSlotType = 1;
			TooltipWidget->UpdateWidget(EquipmentSlotIndex);
			ItemButton->SetToolTip(TooltipWidget);

			//Styling Button
			auto BG_Icon = InventorySystem->RarityData->GetRarityBGIcon(ItemInfo.Rarity);
			NormalSlateBrush.SetResourceObject(BG_Icon);
			auto BG_Color = InventorySystem->RarityData->GetRarityColor(ItemInfo.Rarity);
			NormalSlateBrush.OutlineSettings.Color = FSlateColor(BG_Color);
			
		}
		else
		{
			ItemButton->SetToolTip(nullptr);
			auto BG_Icon = InventorySystem->InventorySystemData->GetItemTypeBGIcon(EquipmentSlotIndex);
			NormalSlateBrush.SetResourceObject(BG_Icon);

			NormalSlateBrush.OutlineSettings.Color = FSlateColor(FColor(12, 12, 12));
		}
		
		ButtonStyle.SetNormal(NormalSlateBrush);

		NormalSlateBrush.OutlineSettings.Color = FSlateColor(FColor(255, 255, 255));
		ButtonStyle.SetHovered(NormalSlateBrush);
		ButtonStyle.SetPressed(NormalSlateBrush);

		ItemButton->SetStyle(ButtonStyle);
	}

}

void UEquipmentSlotWidget::OnClickedItemIcon()
{
	if (InventoryInterface && InventorySystem && ItemInfo.ItemClass)
	{
		InventoryInterface->RemoveAttachedItem(EquipmentSlotIndex, ItemInfo , true);

		InventorySystem->AddItem(ItemInfo);

		(InventorySystem->InventoryWidget)->RefreshInventorySlots();
		(InventorySystem->InventoryWidget)->RefreshEquipmentSlots();
		(InventorySystem->InventoryWidget)->RefreshStatStatus();
	}
}
