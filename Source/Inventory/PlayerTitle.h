// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerTitle : uint8
{
	None            UMETA(DisplayName = "없음"),
    Novice          UMETA(DisplayName = "견습 모험가"),
    Veteran         UMETA(DisplayName = "노련한 사냥꾼"),
    Blacksmith      UMETA(DisplayName = "대장장이의 친구"),
    TreasureHunter  UMETA(DisplayName = "보물 사냥꾼"), 
    ChosenOne       UMETA(DisplayName = "선택받은 자")
};
