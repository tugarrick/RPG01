// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ItemOptionWidget.h"
#include "Components/Button.h"
#include "Interface/InventoryInterface.h"
#include "Component/InventorySystemComponent.h"

bool UItemOptionWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	if (DropButton)
	{
		DropButton->OnClicked.AddDynamic(this, &UItemOptionWidget::OnClickedDropButton);
	}

	InventoryInterface = TScriptInterface<IInventoryInterface>(GetOwningPlayer()->GetPawn());


	if (InventoryInterface)
	{
		InventorySystem = InventoryInterface->GetInventorySystem();
	}

	return true;
}

void UItemOptionWidget::OnClickedDropButton()
{
	if (InventorySystem)
	{
		InventorySystem->DropItem(InventoryIndex, ItemInfo);
		RemoveFromParent();
	}
}

void UItemOptionWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	RemoveFromParent();
}
