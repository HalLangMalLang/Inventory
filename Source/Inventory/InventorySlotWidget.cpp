// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"
#include "InventoryGameInstance.h"
#include "InventoryCharacter.h"
#include "Components\Button.h"

void UInventorySlotWidget::NativeConstruct()
{
	// 각각의 이벤트르 동적 바인딩 //
	ItemButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnSlotClicked);

	ItemButton->OnHovered.AddDynamic(this, &UInventorySlotWidget::OnSlotHovered);

	ItemButton->OnUnhovered.AddDynamic(this, &UInventorySlotWidget::OnSlotUnHovered);

}

void UInventorySlotWidget::UpdateSlot()
{
	if (ItemSlotData->ItemKey != -1)
	{
		if (UInventoryGameInstance* InventoryGameInstance = Cast<UInventoryGameInstance>(GetGameInstance()))
		{
			if (FItemData* ItemData = InventoryGameInstance->FindItem(ItemSlotData->ItemKey))
			{
				ItemImage->SetBrushFromTexture(ItemData->ItemIcon);
				Itemquantity->SetText(FText::AsNumber(ItemSlotData->ItemCount));
			}
		}
	}
	else
	{
		ItemImage->SetBrushFromTexture(nullptr);
		Itemquantity->SetText(FText::GetEmpty());
	}
}

void UInventorySlotWidget::InitSlot(FInventorySlotData* SlotData)
{
	ItemSlotData = SlotData;
	UpdateSlot();
}

void UInventorySlotWidget::OnSlotClicked()
{
	if (ItemSlotData->ItemKey != -1)
	{
		OnSlotClick.Execute(ItemSlotData->ItemKey);
	}
}

void UInventorySlotWidget::OnSlotHovered()
{
	APlayerController* PlayerController = GetOwningPlayer();

	if (ItemInfoWidgetInstance && PlayerController)
	{
		FVector2D MousePosition;
		PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
		ItemInfoWidgetInstance->SetPositionInViewport(MousePosition + FVector2D(20.f, 50.f));

		if (ItemSlotData->ItemKey != -1 && ItemInfoWidgetInstance)
		{
			if (UInventoryGameInstance* InventoryGameInstance = Cast<UInventoryGameInstance>(GetGameInstance()))
			{
				if (FItemData* ItemData = InventoryGameInstance->FindItem(ItemSlotData->ItemKey))
				{
					ItemInfoWidgetInstance->UpdateText(ItemData->ItemName, ItemData->Description, ItemSlotData->ItemCount);
					ItemInfoWidgetInstance->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
	}
}

void UInventorySlotWidget::OnSlotUnHovered()
{
	if (ItemInfoWidgetInstance && ItemInfoWidgetInstance->GetVisibility() == ESlateVisibility::Visible)
	{
		ItemInfoWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
	}
}
