// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/InteractableItems.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/InteractPromptWidget.h"
#include "DataAsset/RarityData.h"

AInteractableItems::AInteractableItems()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	StaticMeshComponent->SetSimulatePhysics(true);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(StaticMeshComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void AInteractableItems::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (ItemDataTable)
	{
		const auto RowName = FName(UEnum::GetDisplayValueAsText(ItemName).ToString());

		auto Row = ItemDataTable->FindRow<FItemInfomation>(RowName, "");

		if (Row)
		{
			ItemInfo = *Row;
			StaticMeshComponent->SetStaticMesh(ItemInfo.StaticMesh);	
		}
		else
		{
			StaticMeshComponent->SetStaticMesh(DefaultStaticMesh);
		}
	}
	
	
}

void AInteractableItems::I_Interact(AActor* InActor)
{

	if (auto PlayerInteractInterface = TScriptInterface<IInteractInterface>(InActor))
	{
		PlayerInteractInterface->I_Interact(this);
	}

	Destroy();
}

void AInteractableItems::I_InRange()
{
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(true);
	}
}

void AInteractableItems::I_OutOfRange()
{
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(false);
	}
}

void AInteractableItems::UpdateData()
{
	if (ItemInfo.ItemClass)
	{
		StaticMeshComponent->SetStaticMesh(ItemInfo.StaticMesh);

		if (InteractPromptWidget)
		{
			if (RarityData)
			{
				InteractPromptWidget->UpdateText(
					FText::FromString(ItemInfo.ItemName.ToString()),
					RarityData->Colors[(int)ItemInfo.Rarity]);
			}
		}
	}
	else 
	{
		StaticMeshComponent->SetStaticMesh(DefaultStaticMesh);
	}
}

void AInteractableItems::BeginPlay()
{
	Super::BeginPlay();
	if (WidgetComponent && InteractPromptWidgetClass)
	{
		WidgetComponent->SetWidgetClass(InteractPromptWidgetClass);
		WidgetComponent->SetVisibility(false);
		InteractPromptWidget = Cast<UInteractPromptWidget>(WidgetComponent->GetWidget());
	}
	UpdateData();
}


