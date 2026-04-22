// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "ItemInfoWidget.h"
#include "InventorySlotWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSlotClick, int32, ItemKey);

UCLASS()
class INVENTORY_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// 슬롯의 이미지
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	// 아이템의 수량
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Itemquantity;

	// 슬롯을 클릭했을때 처리
	UPROPERTY(meta = (BindWidget))
	class UButton* ItemButton;

	virtual void NativeConstruct() override;

public:
	void UpdateSlot();

	void InitSlot(FInventorySlotData* SlotData);

	UItemInfoWidget* ItemInfoWidgetInstance = nullptr;

	UFUNCTION()
	void OnSlotClicked();

	UFUNCTION()
	void OnSlotHovered();

	UFUNCTION()
	void OnSlotUnHovered();

	FOnSlotClick OnSlotClick;

private:
	FInventorySlotData* ItemSlotData;
};
