// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventorySlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/InventoryWidget.h"
#include "Widget/TooltipWidget.h"
#include "Widget/ItemOptionWidget.h"
#include "Component/InventorySystemComponent.h"
#include "DataAsset/InventorySystemData.h"
#include "DataAsset/RarityData.h"
#include "Interface/InventoryInterface.h"



bool UInventorySlotWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnClickedItemIcon);
		ItemButton->OnHovered.AddDynamic(this, &UInventorySlotWidget::OnHoveredItemIcon);
		ItemButton->OnUnhovered.AddDynamic(this, &UInventorySlotWidget::OnUnhoveredItemIcon);
	}
	
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

void UInventorySlotWidget::UpdateWidget()
{
	if (!InventorySystem) return;
	if (!InventorySystem->RarityData) return;

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

	if (ItemQuantity)
	{
		if (ItemInfo.ItemClass && ItemInfo.Stack > 1)
		{
			auto StackText = FText::FromString(FString::Printf(TEXT("%d"), ItemInfo.Stack));

			ItemQuantity->SetText(StackText);
			ItemQuantity->SetVisibility(ESlateVisibility::Visible);

		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (ItemButton)
	{
		if (ItemInfo.ItemClass)
		{

			//Styling Button
			FButtonStyle ButtonStyle = FButtonStyle();
			auto BG_Icon = InventorySystem->RarityData->GetRarityBGIcon(ItemInfo.Rarity);
			auto BG_Color = InventorySystem->RarityData->GetRarityColor(ItemInfo.Rarity);

			auto NormalSlateBrush = FSlateBrush();
			NormalSlateBrush.SetResourceObject(BG_Icon);
			NormalSlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;

			NormalSlateBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
			NormalSlateBrush.OutlineSettings.Color = FSlateColor(BG_Color);
			NormalSlateBrush.OutlineSettings.CornerRadii = FVector4(6, 6, 6, 6);
			NormalSlateBrush.OutlineSettings.Width = 2.0f;

			ButtonStyle.SetNormal(NormalSlateBrush);

			NormalSlateBrush.OutlineSettings.Color = FSlateColor(FColor(255,255,255));
			ButtonStyle.SetHovered(NormalSlateBrush);
			ButtonStyle.SetPressed(NormalSlateBrush);

			ItemButton->SetStyle(ButtonStyle);
		}
		else
		{
			ItemButton->SetToolTip(nullptr);
		}
	}
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!InventorySystem) return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (!InventorySystem->InventorySystemData) return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (ItemInfo.ItemClass)
	{
		if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				3.0f,
				FColor::Green,
				TEXT("Right Click")
			);

			ItemOptionWidget = CreateWidget<UItemOptionWidget>(GetOwningPlayer(), InventorySystem->InventorySystemData->ItemOptionWidgetClass);
			ItemOptionWidget->AddToViewport(1);

			FVector2D MousePosition;
			GetWorld()->GetGameViewport()->GetMousePosition(MousePosition);

			ItemOptionWidget->SetPositionInViewport(FVector2D(MousePosition.X - 75.0f, MousePosition.Y - 30.0f));
			
			ItemOptionWidget->InventoryIndex = InventoryIndex;
			ItemOptionWidget->ItemInfo = ItemInfo;
			
		}
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

}

void UInventorySlotWidget::OnClickedItemIcon()
{

	if (ItemInfo.ItemClass && (int)ItemInfo.ItemType <= 6) // Only Equip Item that can euip
	{
		OnUnhoveredItemIcon();//Hide Stats Delta after equip item

		EquipmentSlotIndex = (int)ItemInfo.ItemType;
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				3.0f,
				FColor::Green,
				FString::Printf(TEXT("EquipmentSlotIndex = %d"), EquipmentSlotIndex)
			);
		}


		if (InventoryInterface && InventorySystem)
		{
			InventorySystem->RemoveItem(InventoryIndex);

			if (auto ItemInfoRef = InventorySystem->AttachedEquipment.Find(EquipmentSlotIndex))
			{	
				InventorySystem->AddItem(*ItemInfoRef);//Add attached item back to inventory
				InventoryInterface->RemoveAttachedItem(EquipmentSlotIndex, *ItemInfoRef, false);
			}

			InventoryInterface->AddAttachedItem(EquipmentSlotIndex, ItemInfo);
			
			(InventorySystem->InventoryWidget)->RefreshEquipmentSlots();
			(InventorySystem->InventoryWidget)->RefreshInventorySlots();
			(InventorySystem->InventoryWidget)->RefreshStatStatus();
		}
	}
}

void UInventorySlotWidget::OnHoveredItemIcon()
{
	if (InventorySystem == nullptr) return;
	if (ItemInfo.ItemClass == nullptr) return;
	if (ItemButton == nullptr) return;

	EquipmentSlotIndex = int(ItemInfo.ItemType);

	InventorySystem->InventoryWidget->ShowStatsDelta(EquipmentSlotIndex, ItemInfo);

	//Tooltip Widget
	auto TooltipWidget = CreateWidget<UTooltipWidget>(GetOwningPlayer(), InventorySystem->InventorySystemData->TooltipWidgetClass);
	TooltipWidget->ItemInfo = ItemInfo;
	TooltipWidget->CurrentSlotType = 0; // 0 is Inventory Slot
	TooltipWidget->UpdateWidget(EquipmentSlotIndex);

	ItemButton->SetToolTip(TooltipWidget);

}

void UInventorySlotWidget::OnUnhoveredItemIcon()
{
	if (InventorySystem == nullptr) return;

	InventorySystem->InventoryWidget->HideStatsDelta();
}
