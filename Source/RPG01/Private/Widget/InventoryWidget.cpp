// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryWidget.h"
#include "Components/GridPanel.h"
#include "Widget/InventorySlotWidget.h"
#include "Components/Border.h"
#include "Character/PreviewTreyCharacter.h"
#include "Component/StatComponent.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Component/InventorySystemComponent.h"
#include "DataAsset/InventorySystemData.h"
#include "Interface/InventoryInterface.h"
#include "Interface/StatInterface.h"


bool UInventoryWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	if (GetOwningPlayer())
	{
		InventoryInterface = TScriptInterface<IInventoryInterface>(GetOwningPlayer()->GetPawn());
		StatInterface = TScriptInterface<IStatInterface>(GetOwningPlayer()->GetPawn());
	}
	
	if (InventoryInterface)
	{
		InventorySystem = InventoryInterface->GetInventorySystem();
	}

	return true;
}

void UInventoryWidget::BuildInventory()
{
	if (InventorySystem && InventorySystem->InventorySystemData->InventorySlotWidgetClass && InventoryGrid)
	{
		InventoryGrid->ClearChildren();
		int Index = 0;
		for (int row = 1; row <= 6; row++)
		{
			for (int col = 1; col <= 6; col++)
			{
				auto InventorySlotWidget = CreateWidget<UInventorySlotWidget>(GetOwningPlayer(), InventorySystem->InventorySystemData->InventorySlotWidgetClass);
				InventorySlotWidget->InventoryIndex = Index;
				InventorySlotWidget->ItemInfo = InventorySystem->Inventory[Index];
				InventorySlotWidget->UpdateWidget();

				InventoryGrid->AddChildToGrid(InventorySlotWidget, row, col);

				Index++;
			}
		}
		
	}
}

void UInventoryWidget::ShowStatsDelta(int EquipmentSlotIndex, FItemInfomation& ItemInfo)
{
	if (!InventoryInterface || !StatInterface) return;
	if (ItemInfo.ItemClass == nullptr || ItemInfo.Stats.IsEmpty()) return;
	if (!InventorySystem) return;


	auto ItemInfoRef = InventorySystem->AttachedEquipment.Find(EquipmentSlotIndex);

	for (auto StatData : ItemInfo.Stats)
	{
		float Delta = StatData.Value;
		if (ItemInfoRef)
		{
			Delta -= *(ItemInfoRef->Stats.Find(StatData.Key));
		}

		if (Delta != 0.0f)
		{
			FString DeltaString = TEXT("");
			FSlateColor Color;
			if (Delta > 0.0f)
			{
				DeltaString.Append(TEXT("+"));
				Color = FSlateColor(FColor::Green);
			}
			else
			{
				Color = FSlateColor(FColor::Red);
			}

			DeltaString.Append(FString::FormatAsNumber(int(Delta)));

			switch (StatData.Key)
			{
			case EStat::Health:
				if (HealthDelta && HealthUnderline)
				{
					HealthDelta->SetText(FText::FromString(DeltaString));
					HealthDelta->SetColorAndOpacity(Color);
					HealthDelta->SetVisibility(ESlateVisibility::Visible);
					HealthUnderline->SetBrushTintColor(Color);
					HealthUnderline->SetVisibility(ESlateVisibility::Visible);
				}
				break;
			case EStat::Stamina:
				if (StaminaDelta && StaminaUnderline)
				{	
					StaminaDelta->SetText(FText::FromString(DeltaString));
					StaminaDelta->SetColorAndOpacity(Color);
					StaminaDelta->SetVisibility(ESlateVisibility::Visible);
					StaminaUnderline->SetBrushTintColor(Color);
					StaminaUnderline->SetVisibility(ESlateVisibility::Visible);
				}
				break;
			case EStat::Mana:
				if (ManaDelta && ManaUnderline)
				{
					ManaDelta->SetText(FText::FromString(DeltaString));
					ManaDelta->SetColorAndOpacity(Color);
					ManaDelta->SetVisibility(ESlateVisibility::Visible);
					ManaUnderline->SetBrushTintColor(Color);
					ManaUnderline->SetVisibility(ESlateVisibility::Visible);
				}
				break;
			case EStat::Armor:
				if (ArmorDelta && ArmorUnderline)
				{
					ArmorDelta->SetText(FText::FromString(DeltaString));
					ArmorDelta->SetColorAndOpacity(Color);
					ArmorDelta->SetVisibility(ESlateVisibility::Visible);
					ArmorUnderline->SetBrushTintColor(Color);
					ArmorUnderline->SetVisibility(ESlateVisibility::Visible);
				}
				break;
			case EStat::PhysicalDamage:
				if (PhysicalDamageDelta && PhysicalDamageUnderline)
				{
					PhysicalDamageDelta->SetText(FText::FromString(DeltaString));
					PhysicalDamageDelta->SetColorAndOpacity(Color);
					PhysicalDamageDelta->SetVisibility(ESlateVisibility::Visible);
					PhysicalDamageUnderline->SetBrushTintColor(Color);
					PhysicalDamageUnderline->SetVisibility(ESlateVisibility::Visible);
				}
				break;
			case EStat::MagicalDamage:
				if (MagicalDamageDelta && MagicalDamageUnderline)
				{
					MagicalDamageDelta->SetText(FText::FromString(DeltaString));
					MagicalDamageDelta->SetColorAndOpacity(Color);
					MagicalDamageDelta->SetVisibility(ESlateVisibility::Visible);
					MagicalDamageUnderline->SetBrushTintColor(Color);
					MagicalDamageUnderline->SetVisibility(ESlateVisibility::Visible);
				}
				break;
			case EStat::MovementSpeed:
				if (MovementSpeedDelta && MovementSpeedUnderline)
				{
					MovementSpeedDelta->SetText(FText::FromString(DeltaString));
					MovementSpeedDelta->SetColorAndOpacity(Color);
					MovementSpeedDelta->SetVisibility(ESlateVisibility::Visible);
					MovementSpeedUnderline->SetBrushTintColor(Color);
					MovementSpeedUnderline->SetVisibility(ESlateVisibility::Visible);
				}
				break;
			case EStat::AttackSpeed:
				if (AttackSpeedDelta && AttackSpeedUnderline)
				{
					if (Delta > 0.0f) DeltaString = TEXT("+");
					else DeltaString = TEXT("");
					DeltaString.Append(FString::Printf(TEXT("%.1f"), Delta / 100.0f));
					AttackSpeedDelta->SetText(FText::FromString(DeltaString));
					AttackSpeedDelta->SetColorAndOpacity(Color);
					AttackSpeedDelta->SetVisibility(ESlateVisibility::Visible);
					AttackSpeedUnderline->SetBrushTintColor(Color);
					AttackSpeedUnderline->SetVisibility(ESlateVisibility::Visible);
				}
				break;
			case EStat::Cooldown:
				if (CooldownDelta && CooldownUnderline)
				{
					if (Delta > 0.0f) DeltaString = TEXT("+");
					else DeltaString = TEXT("");
					DeltaString.Append(FString::Printf(TEXT("%d%%"), (int)Delta));
					CooldownDelta->SetText(FText::FromString(DeltaString));
					CooldownDelta->SetColorAndOpacity(Color);
					CooldownDelta->SetVisibility(ESlateVisibility::Visible);
					CooldownUnderline->SetBrushTintColor(Color);
					CooldownUnderline->SetVisibility(ESlateVisibility::Visible);
				}
				break;
			}
		}
	}

}

void UInventoryWidget::HideStatsDelta()
{
	if (HealthDelta && HealthUnderline)
	{
		HealthDelta->SetVisibility(ESlateVisibility::Hidden);
		HealthUnderline->SetVisibility(ESlateVisibility::Hidden);
	}

	if (StaminaDelta && StaminaUnderline)
	{
		StaminaDelta->SetVisibility(ESlateVisibility::Hidden);
		StaminaUnderline->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ManaDelta && ManaUnderline)
	{
		ManaDelta->SetVisibility(ESlateVisibility::Hidden);
		ManaUnderline->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ArmorDelta && ArmorUnderline)
	{
		ArmorDelta->SetVisibility(ESlateVisibility::Hidden);
		ArmorUnderline->SetVisibility(ESlateVisibility::Hidden);
	}

	if (PhysicalDamageDelta && PhysicalDamageUnderline)
	{
		PhysicalDamageDelta->SetVisibility(ESlateVisibility::Hidden);
		PhysicalDamageUnderline->SetVisibility(ESlateVisibility::Hidden);
	}

	if (MagicalDamageDelta && MagicalDamageUnderline)
	{
		MagicalDamageDelta->SetVisibility(ESlateVisibility::Hidden);
		MagicalDamageUnderline->SetVisibility(ESlateVisibility::Hidden);
	}

	if (MovementSpeedDelta && MovementSpeedUnderline)
	{
		MovementSpeedDelta->SetVisibility(ESlateVisibility::Hidden);
		MovementSpeedUnderline->SetVisibility(ESlateVisibility::Hidden);
	}

	if (AttackSpeedDelta && AttackSpeedUnderline)
	{
		AttackSpeedDelta->SetVisibility(ESlateVisibility::Hidden);
		AttackSpeedUnderline->SetVisibility(ESlateVisibility::Hidden);
	}

	if (CooldownDelta && CooldownUnderline)
	{
		CooldownDelta->SetVisibility(ESlateVisibility::Hidden);
		CooldownUnderline->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInventoryWidget::RefreshEquipmentSlots()
{
	if (InventorySystem && EquipmentBox)
	{
		EquipmentBox->ClearChildren();

		InventorySystem->EquipmentPreviewWidget =
			CreateWidget<UUserWidget>(GetOwningPlayer(), InventorySystem->InventorySystemData->EquipmentPreviewWidgetClass);
		EquipmentBox->AddChild(InventorySystem->EquipmentPreviewWidget);
	}
}

void UInventoryWidget::RefreshInventorySlots()
{
	BuildInventory();
}

void UInventoryWidget::RefreshStatStatus()
{
	if (!StatInterface) return;
	if (HealthValue)
	{
		auto ValueString = FString::FormatAsNumber(FMath::FloorToInt(StatInterface->GetMaxStat(EStat::Health)));
		HealthValue->SetText(FText::FromString(ValueString));
	}

	if (StaminaValue)
	{
		auto ValueString = FString::FormatAsNumber(FMath::FloorToInt(StatInterface->GetMaxStat(EStat::Stamina)));
		StaminaValue->SetText(FText::FromString(ValueString));
	}

	if (ManaValue)
	{
		auto ValueString = FString::FormatAsNumber(FMath::FloorToInt(StatInterface->GetMaxStat(EStat::Mana)));
		ManaValue->SetText(FText::FromString(ValueString));
	}

	if (ArmorValue)
	{
		auto ValueString = FString::FormatAsNumber(FMath::FloorToInt(StatInterface->GetMaxStat(EStat::Armor)));
		ArmorValue->SetText(FText::FromString(ValueString));
	}

	if (PhysicalDamageValue)
	{
		auto ValueString = FString::FormatAsNumber(FMath::FloorToInt(StatInterface->GetMaxStat(EStat::PhysicalDamage)));
		PhysicalDamageValue->SetText(FText::FromString(ValueString));
	}

	if (MagicalDamageValue)
	{
		auto ValueString = FString::FormatAsNumber(FMath::FloorToInt(StatInterface->GetMaxStat(EStat::MagicalDamage)));
		MagicalDamageValue->SetText(FText::FromString(ValueString));
	}

	if (MovementSpeedValue)
	{
		auto ValueString = FString::FormatAsNumber(FMath::FloorToInt(StatInterface->GetMaxStat(EStat::MovementSpeed)));
		MovementSpeedValue->SetText(FText::FromString(ValueString));
	}

	if (AttackSpeedValue)
	{
		auto ValueString = FString::Printf(TEXT("%.1f"), StatInterface->GetMaxStat(EStat::AttackSpeed));
		AttackSpeedValue->SetText(FText::FromString(ValueString));
	}

	if (CooldownValue)
	{
		FString ValueString = FString::FormatAsNumber(FMath::FloorToInt32(StatInterface->GetMaxStat(EStat::Cooldown)));
		ValueString.Append(TEXT("%"));
		CooldownValue->SetText(FText::FromString(ValueString));
	}
}


