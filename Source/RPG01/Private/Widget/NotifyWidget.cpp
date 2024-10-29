// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NotifyWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UNotifyWidget::SetupData(TObjectPtr<UTexture> BG, TObjectPtr<UTexture> Icon, FString Name, int Stack)
{
	if (NotifyBar)
	{
		NotifyBar->SetBrushFromTexture(Cast<UTexture2D>(BG));
	}
	if (ItemIcon) 
	{
		ItemIcon->SetBrushResourceObject(Icon);
	}
	if (ItemName)
	{
		ItemName->SetText(FText::FromString(Name));
	}
	if (ItemStack)
	{
		FString StackString = FString::Printf(TEXT("x%d"),Stack);
		ItemStack->SetText(FText::FromString(StackString));
	}

}

void UNotifyWidget::ShowNotify()
{
	if (ShowNotifyAnimation)
	{
		PlayAnimation(ShowNotifyAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UNotifyWidget::RemoveNotify, 4.5f, false);
	}
}

void UNotifyWidget::RemoveNotify()
{
	RemoveFromParent();
}


