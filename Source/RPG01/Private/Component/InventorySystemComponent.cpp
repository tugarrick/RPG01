// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventorySystemComponent.h"
#include "DataAsset/InventorySystemData.h"
#include "Character/PreviewTreyCharacter.h"
#include "Actor/InteractableItems.h"
#include "Widget/NotifyWidget.h"
#include "Widget/InterfaceWidget.h"
#include "Widget/InventoryWidget.h"


UInventorySystemComponent::UInventorySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventorySystemComponent::Init(APlayerController* Controller)
{
	PlayerController = Controller;
}

void UInventorySystemComponent::OpenInventory()
{
	if (!PlayerController || !InventorySystemData) return;
	if (!InventorySystemData->PreviewTreyCharacterClass) return;

	auto SpawnTransform = FTransform(FRotator(0, 0, 90), FVector(1000000, 0, 0), FVector(1, 1, 1));
	PreviewTreyCharacter = Cast<APreviewTreyCharacter>(GetWorld()->SpawnActor(InventorySystemData->PreviewTreyCharacterClass, &SpawnTransform));
	for (auto AttachedItem : AttachedEquipment)
	{
		PreviewTreyCharacter->AttachItem(AttachedItem.Key, AttachedItem.Value);
	}

	InterfaceWidget = CreateWidget<UInterfaceWidget>(PlayerController, InventorySystemData->InterfaceWidgetClass);
	InterfaceWidget->AddToViewport();
	InterfaceWidget->SetIsFocusable(true);

	InventoryWidget = InterfaceWidget->InventoryWidget;
	InventoryWidget->RefreshInventorySlots();
	InventoryWidget->RefreshStatStatus();
	InventoryWidget->HideStatsDelta();

	PlayerController->bShowMouseCursor = true;

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetWidgetToFocus(InterfaceWidget->TakeWidget());
	PlayerController->SetInputMode(InputModeGameAndUI);

	//UGameplayStatics::SetGamePaused(this, true);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			3.0f,
			FColor::Blue,
			TEXT("Open Inventory")
		);
	}
}

void UInventorySystemComponent::CloseInventory()
{
	if (!PlayerController || !InventorySystemData) return;


	if (PreviewTreyCharacter)
	{
		for (auto AttachedActor : PreviewTreyCharacter->AttachedActors)
		{
			AttachedActor.Value->Destroy();
		}
		PreviewTreyCharacter->Destroy();
	}

	InterfaceWidget->SetIsFocusable(false);
	InterfaceWidget->RemoveFromParent();
	InterfaceWidget = nullptr;

	PlayerController->bShowMouseCursor = false;

	FInputModeGameOnly InputModeGameOnly;
	PlayerController->SetInputMode(InputModeGameOnly);

	//UGameplayStatics::SetGamePaused(this, false);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			3.0f,
			FColor::Blue,
			TEXT("Close Inventory")
		);
	}
	
}

void UInventorySystemComponent::RemoveItem(int InventoryIndex)
{
	if (Inventory[InventoryIndex].ItemClass)
	{
		Inventory[InventoryIndex] = FItemInfomation();
	}
}

void UInventorySystemComponent::AddItem(FItemInfomation& ItemInfo)
{
	bool bItemFound = false;
	int ItemFoundIndex = -1;

	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemClass == ItemInfo.ItemClass
			&& Inventory[i].Stack < Inventory[i].MaxStack)
		{
			bItemFound = true;
			ItemFoundIndex = i;
			break;
		}
	}

	if (bItemFound)
	{
		Inventory[ItemFoundIndex].Stack++;
	}
	else
	{
		int EmptySlotIndex = GetEmptySlotIndex();
		if (EmptySlotIndex >= 0)
		{
			Inventory[EmptySlotIndex] = ItemInfo;
		}
	}
}

int UInventorySystemComponent::GetEmptySlotIndex()
{
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemClass == nullptr)
		{
			return i;
		}
	}
	return -1;
}

void UInventorySystemComponent::DropItem(int InventoryIndex, FItemInfomation& ItemInfo)
{
	if (!InventorySystemData || !InventorySystemData->InteractableItemsClass) return;
	if (!PlayerController) return;
	
	if (auto OwningCharacter = PlayerController->GetCharacter())
	{
		auto SpawnLocation = OwningCharacter->GetActorLocation() + OwningCharacter->GetActorForwardVector() * 50.0f;
		auto SpawnTransform = FTransform(FRotator(0, 0, 0), SpawnLocation, FVector(1, 1, 1));
		auto InteractableItem = Cast<AInteractableItems>(GetWorld()->SpawnActor(InventorySystemData->InteractableItemsClass, &SpawnTransform));
		InteractableItem->ItemInfo = ItemInfo;
		InteractableItem->UpdateData();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				3.0f,
				FColor::Blue,
				FString::Printf(TEXT("Drop Item : %.1f %.1f %.1f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z)
			);
		}
	}

	RemoveItem(InventoryIndex);
	InventoryWidget->RefreshInventorySlots();
}



void UInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}


//void UInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//}

