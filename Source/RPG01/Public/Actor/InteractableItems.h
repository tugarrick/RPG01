// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/InteractInterface.h"
#include "GameFramework/Actor.h"
#include "Enum/ItemName.h"
#include "Struct/ItemInfomation.h"
#include "InteractableItems.generated.h"

class UInteractPromptWidget;
class UWidgetComponent;
class URarityData;
UCLASS()
class RPG01_API AInteractableItems : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableItems();
	//virtual void Tick(float DeltaTime) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void I_Interact(AActor* InActor) override;

	virtual void I_InRange() override;

	virtual void I_OutOfRange() override;

	void UpdateData();

protected:
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Item Info")
	TObjectPtr<UStaticMesh> DefaultStaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item Info")
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditAnywhere, Category = "Item Info")
	EItemName ItemName = EItemName::None;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UInteractPromptWidget> InteractPromptWidgetClass;

	UPROPERTY()
	TObjectPtr<UInteractPromptWidget> InteractPromptWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY()
	FItemInfomation ItemInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Data Asset")
	TObjectPtr<URarityData> RarityData;

};
