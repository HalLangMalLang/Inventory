// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoWidget.h"
#include "Components\TextBlock.h"

void UItemInfoWidget::UpdateText(FString ItemName, FText ItemDescription, int32 ItemCount)
{
	ItemNameText->SetText(FText::FromString(ItemName));
	ItemDescriptionText->SetText(ItemDescription);
	ItemCountText->SetText(FText::FromString(FString::Printf(TEXT("개수 : %d"), ItemCount)));
}
