// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InterfaceWidget.generated.h"

class UInventoryWidget;
class USkillWidget;

UCLASS()
class RPG01_API UInterfaceWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillWidget> SkillWidget;
};
