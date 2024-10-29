// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/ItemInfomation.h"
#include "NotifyBoxWidget.generated.h"

class UVerticalBox;
class URarityData;
class UNotifyWidget;

UCLASS()
class RPG01_API UNotifyBoxWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	static void InitInstance(APlayerController* PlayerController, TSubclassOf<UNotifyBoxWidget> NotifyBoxWidgetClass);
	static UNotifyBoxWidget* Get();

	void AddNotify(const FItemInfomation& ItemInfo, TSubclassOf<UNotifyWidget> NotifyWidgetClass);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Data Asset");
	TObjectPtr<URarityData> RarityData;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> NotifyBox;

protected:
	static UNotifyBoxWidget* Instance;

};
