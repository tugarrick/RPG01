// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/ItemInfomation.h"
#include "ItemOptionWidget.generated.h"

class UButton;
class IInventoryInterface;
class UInventorySystemComponent;

UCLASS()
class RPG01_API UItemOptionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	UFUNCTION()
	void OnClickedDropButton();
protected:
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
public:
	UPROPERTY()
	TObjectPtr<UInventorySystemComponent> InventorySystem;

	UPROPERTY()
	int InventoryIndex = 0;

	UPROPERTY()
	FItemInfomation ItemInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> DropButton;
		
protected:
	UPROPERTY()
	TScriptInterface<IInventoryInterface> InventoryInterface;;
};
