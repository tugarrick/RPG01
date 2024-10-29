// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotifyWidget.generated.h"

class UImage;
class UTextBlock;
class UBorder;

UCLASS()
class RPG01_API UNotifyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetupData(TObjectPtr<UTexture> BG, TObjectPtr<UTexture> Icon, FString Name, int Stack);
	void ShowNotify();
	void RemoveNotify();
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemStack;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> NotifyBar;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> ShowNotifyAnimation;
};
