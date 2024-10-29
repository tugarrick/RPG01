// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InterfaceWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

bool UInterfaceWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	return true;
}

