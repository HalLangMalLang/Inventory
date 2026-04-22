// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Components\WrapBox.h"
#include "Components\Widget.h"
#include "Components\WidgetComponent.h"
#include "InventorySlotWidget.h"

#include "InventoryGameInstance.h"

#include "InventoryCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() {}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::InventoryToggle(APlayerController* PlayerController, bool Active)
{
	if (LoadInventory(PlayerController))
	{
		if (Active)
		{
			PlayerController->bShowMouseCursor = true;
			PlayerController->SetInputMode(FInputModeGameAndUI());
			InventoryWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			InventoryWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;
		}
	}
}


bool UInventoryComponent::LoadInventory(APlayerController* PlayerController)
{
	if (!InventoryWidgetClass || !ItemInfoWidgetClass)
	{
		return false;
	}

	if (!InventoryWidgetInstance)
	{
		InventoryWidgetInstance = CreateWidget<UUserWidget>(PlayerController, InventoryWidgetClass);
		if (InventoryWidgetInstance)
		{
			InventoryWidgetInstance->AddToViewport();
			InventoryWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			return false;
		}
	}

	if (!ItemInfoWidgetInstance)
	{
		ItemInfoWidgetInstance = CreateWidget<UItemInfoWidget>(PlayerController, ItemInfoWidgetClass);
		if (ItemInfoWidgetInstance)
		{
			ItemInfoWidgetInstance->AddToViewport();
			ItemInfoWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			return false;
		}
	}

	if (!InventoryWrapBox)
	{
		InventoryWrapBox = Cast<UWrapBox>(InventoryWidgetInstance->GetWidgetFromName(TEXT("Wrapbox")));
		if (!InventoryWrapBox)
		{
			return false;
		}
	}

	if (InventoryWrapBox)
	{
		if (InventoryWrapBox->GetChildrenCount() != MaxInventoryCapacity)
		{
			Inventory.SetNum(MaxInventoryCapacity);
			InventoryWrapBox->ClearChildren();

			for (int32 i = 0; i < MaxInventoryCapacity; i++)
			{
				if (UInventorySlotWidget* InventorySlot = CreateWidget<UInventorySlotWidget>(PlayerController, InventorySlotWidgetClass))
				{
					Inventory[i].Value = InventorySlot;
					InventoryWrapBox->AddChildToWrapBox(InventorySlot);
					InventorySlot->InitSlot(&Inventory[i].Key);
					InventorySlot->ItemInfoWidgetInstance = ItemInfoWidgetInstance;
					InventorySlot->OnSlotClick.BindDynamic(this, &UInventoryComponent::ItemClickHandle);
				}
				else
				{
					return false;
				}
			}
		}
	}

	return true;
}

void UInventoryComponent::AddItem(APlayerController* PlayerController, int32 ItemKey, int32 Count)
{
	if (InventoryMap.Contains(ItemKey))
	{
		Inventory[InventoryMap[ItemKey]].Key.ItemCount += Count;
		Inventory[InventoryMap[ItemKey]].Value->UpdateSlot();
	}
	else
	{
		bool ItemAddCheck = false;
		for (int32 i = 0; i < Inventory.Num(); i++)
		{
			if (Inventory[i].Key.ItemKey == -1)
			{
				Inventory[i].Key.ItemKey = ItemKey;
				Inventory[i].Key.ItemCount = Count;
				Inventory[i].Value->UpdateSlot();
				InventoryMap.Add(ItemKey, i);
				ItemAddCheck = true;
				break;
			}
		}

		if (!ItemAddCheck)
		{
			UE_LOG(LogTemp, Log, TEXT("가방이 가득찼습니다."));
		}
	}
}

void UInventoryComponent::ItemClickHandle(int32 ItemKey)
{
	if (AInventoryCharacter* PlayerCharacter = Cast<AInventoryCharacter>(GetOwner()))
	{
		if (UInventoryGameInstance* InventoryGameInstance = Cast<UInventoryGameInstance>(PlayerCharacter->GetGameInstance()))
		{
			if (FItemData* ItemData = InventoryGameInstance->FindItem(ItemKey))
			{
				if (PlayerCharacter->PlayerTitles.Contains(ItemData->RequiredTitle))
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("아이템 사용"));
			
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("아이템 사용 불가"));
				}
			}
		}
	}
}
