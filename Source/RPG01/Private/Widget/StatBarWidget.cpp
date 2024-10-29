// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/StatBarWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UStatBarWidget::Init(EStat InStatType, int32 InStatValue, UTexture* InStatBGIcon)
{
	StatType = InStatType;
	StatValue = InStatValue;
	StatBGIcon = InStatBGIcon;
}

void UStatBarWidget::UpdateData()
{
	if (StatName)
	{
		StatName->SetText(UEnum::GetDisplayValueAsText(StatType));
	}

	if (StatValueText)
	{
		auto ValueString = FString::FormatAsNumber(StatValue);
		switch (StatType)
		{
		case EStat::AttackSpeed:
		case EStat::Cooldown:
			ValueString.Append(TEXT("%"));
			break;

		default:
			break;
		}

		StatValueText->SetText(FText::FromString(ValueString));
	}

	if (StatIcon)
	{
		StatIcon->SetBrushResourceObject(StatBGIcon);
	}

	if (StatStatusIcon)
	{
		if (StatStatusBGIcon != nullptr)
		{
			StatStatusIcon->SetBrushResourceObject(StatStatusBGIcon);
			StatStatusIcon->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			StatStatusIcon->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
