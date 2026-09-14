// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/DebugLogManager.h"

DebugLogManager::DebugLogManager()
{
}

DebugLogManager::~DebugLogManager()
{
}

void DebugLogManager::LogError(const FString& Message, const FString& Category)
{
}

void DebugLogManager::LogWarning(const FString& Message, const FString& Category)
{
}

void DebugLogManager::LogInfo(const FString& Message, const FString& Category)
{
}

void DebugLogManager::LogDebug(const FString& Message, const FString& Category)
{
}

DEFINE_LOG_CATEGORY(AIError);
DEFINE_LOG_CATEGORY(AIWarning);

DEFINE_LOG_CATEGORY(PlayerError);
DEFINE_LOG_CATEGORY(PlayerWarning);

DEFINE_LOG_CATEGORY(EnemyError);
DEFINE_LOG_CATEGORY(EnemyWarning);

DEFINE_LOG_CATEGORY(ProgressionError);
DEFINE_LOG_CATEGORY(ProgressionWarning);

DEFINE_LOG_CATEGORY(EquipmentError);
DEFINE_LOG_CATEGORY(EquipmentWarning);

DEFINE_LOG_CATEGORY(InventoryError);
DEFINE_LOG_CATEGORY(InventoryWarning);