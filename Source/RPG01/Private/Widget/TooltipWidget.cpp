// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TooltipWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/GridPanel.h"
#include "Widget/StatBarWidget.h"
#include "Enum/Stat.h"
#include "Component/InventorySystemComponent.h"
#include "DataAsset/InventorySystemData.h"
#include "DataAsset/RarityData.h"

#include "Interface/InventoryInterface.h"


bool UTooltipWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	if (GetOwningPlayer())
	{
		InventoryInterface = TScriptInterface<IInventoryInterface>(GetOwningPlayer()->GetPawn());
	}

	if (InventoryInterface)
	{
		InventorySystem = InventoryInterface->GetInventorySystem();
	}

	return true;
}

void UTooltipWidget::UpdateWidget(int EquipmentSlotIndex)
{
	if (!InventorySystem) return;
	if (!InventorySystem->InventorySystemData || !InventorySystem->RarityData) return;

	if (ItemIcon)
	{
		ItemIcon->SetBrushResourceObject(ItemInfo.Icon);
	}

	if (ItemName)
	{
		ItemName->SetText(FText::FromName(ItemInfo.ItemName));
		ItemName->SetColorAndOpacity(FSlateColor(InventorySystem->RarityData->GetRarityColor(ItemInfo.Rarity)));
	}

	if (ItemType)
	{	
		ItemType->SetText(UEnum::GetDisplayValueAsText(ItemInfo.ItemType));
	}

	if (ItemRarity)
	{
		ItemRarity->SetText(UEnum::GetDisplayValueAsText(ItemInfo.Rarity));
		ItemRarity->SetColorAndOpacity(FSlateColor(InventorySystem->RarityData->GetRarityColor(ItemInfo.Rarity)));
	}

	if (TooltipBox)
	{
		auto NormalSlateBrush = FSlateBrush();
		NormalSlateBrush.SetResourceObject(InventorySystem->RarityData->GetRarityBGIcon_2(ItemInfo.Rarity));
		NormalSlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
		//NormalSlateBrush.TintColor = FSlateColor(FColor(25, 25, 25));
		NormalSlateBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
		NormalSlateBrush.OutlineSettings.Color = FSlateColor(InventorySystem->RarityData->GetRarityColor(ItemInfo.Rarity));
		NormalSlateBrush.OutlineSettings.CornerRadii = FVector4(6, 6, 6, 6);
		NormalSlateBrush.OutlineSettings.Width = 3.0f;

		TooltipBox->SetBrush(NormalSlateBrush);
	}

	if (ItemLevelRequest)
	{
		ItemLevelRequest->SetText(FText::FromString(FString::Printf(TEXT("Requires Level %d"), ItemInfo.LevelRequest)));
	}


	if (ItemInstruct)
	{
		if (CurrentSlotType == 0) // 0 is Inventory Slot
		{
			ItemInstruct->SetText(FText::FromString(TEXT("CLICK TO EQUIP ITEM")));
			ItemInstruct->SetColorAndOpacity(FSlateColor(FColor(0,255,0)));
		}
		else // 1 is EquipmentSlot
		{
			ItemInstruct->SetText(FText::FromString(TEXT("CLICK TO UNEQUIP ITEM")));
			ItemInstruct->SetColorAndOpacity(FSlateColor(FColor(255,0,0)));
		}
	}

	if (StatsGridPanel)
	{
		if (ItemInfo.ItemClass == nullptr || ItemInfo.Stats.IsEmpty()) return;

		auto ItemInfoRef = InventorySystem->AttachedEquipment.Find(EquipmentSlotIndex);

		int Index = 0;

		for (auto StatData : ItemInfo.Stats)
		{
			//show the delta of this item stats with equipping item stats
			float Delta = StatData.Value;
			if (ItemInfoRef)
			{
				Delta -= *(ItemInfoRef->Stats.Find(StatData.Key));
			}

			auto StatBarWidget = CreateWidget<UStatBarWidget>(GetOwningPlayer(), InventorySystem->InventorySystemData->StatBarWidgetClass);

			StatBarWidget->Init(
				StatData.Key,
				FMath::FloorToInt32(StatData.Value),
				InventorySystem->InventorySystemData->GetStatTypeBGIcon(StatData.Key)
			);

			if (Delta > 0.0f)
			{
				StatBarWidget->StatStatusBGIcon = InventorySystem->InventorySystemData->IncreaseImage;
			}
			else if (Delta < 0.0f)
			{
				StatBarWidget->StatStatusBGIcon = InventorySystem->InventorySystemData->DecreaseImage;
			}

			StatBarWidget->UpdateData();

			StatsGridPanel->AddChildToGrid(StatBarWidget, Index, 0);
			
			Index++;
		}

	}

}
