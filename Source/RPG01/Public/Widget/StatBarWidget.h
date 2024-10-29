// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum/Stat.h"
#include "StatBarWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class RPG01_API UStatBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(EStat StatType, int32 StatValue, UTexture* StatBGIcon);

	void UpdateData();
public:
	UPROPERTY()
	EStat StatType;

	int32 StatValue;

	UPROPERTY()
	TObjectPtr<UTexture> StatBGIcon;

	UPROPERTY()
	TObjectPtr<UTexture> StatStatusBGIcon = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> StatIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatValueText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> StatStatusIcon;
};
