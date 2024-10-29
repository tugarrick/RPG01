// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InteractPromptWidget.h"
#include "Components/TextBlock.h"

bool UInteractPromptWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	return true;
}

void UInteractPromptWidget::UpdateText(FText NewText, FColor NewColor)
{
	if (ItemName)
	{
		ItemName->SetText(NewText);
		ItemName->SetColorAndOpacity(FSlateColor(NewColor));
	}
}
