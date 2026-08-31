// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// ERROR WARNING CATEGORIES 

// Major AI Errors (Problems that cause AI to completely break, crash the game/editor, etc)
DECLARE_LOG_CATEGORY_EXTERN(AIError, Error, All);

// Major Player Errors  (The player breaks in some way or another, e.g. can't move, can't progress, etc)
DECLARE_LOG_CATEGORY_EXTERN(PlayerError, Error, All);

// Major Enemy Errors (The enemy breaks in some way or another, e.g. can't move, can't attack, etc)
DECLARE_LOG_CATEGORY_EXTERN(EnemyError, Error, All);

// Major Progression Errors (e.g Can't progress past an area for some reason)
DECLARE_LOG_CATEGORY_EXTERN(ProgressionError, Error, All);

// Major Equipment Errors (e.g. Can't use any of the equipment, can't use a flashlight, etc)
DECLARE_LOG_CATEGORY_EXTERN(EquipmentError, Error, All);



// WARNING CATEGORIES

// Major AI Warnings (Problems that could cause AI to break, e.g. AI can't find a path, can't see the player, etc)
DECLARE_LOG_CATEGORY_EXTERN(AIWarning, Warning, All);

// Major Player Warnings (The player is doing something that could cause problems, e.g. trying to move through a wall, attempting an invalid action, etc)
DECLARE_LOG_CATEGORY_EXTERN(PlayerWarning, Warning, All);

// Major Enemy Warnings (The enemy is doing something that will cause it to break functionality, e.g. Stuck agaisnt walls, pathfinding issues, attacking issues, state machine problems, etc)
DECLARE_LOG_CATEGORY_EXTERN(EnemyWarning, Warning, All);

// Major Progression Warnings (The player is doing something that will cause them to be unable to progress, e.g. trying to open a door without the key, attempting to use an item in the wrong way, etc)
DECLARE_LOG_CATEGORY_EXTERN(ProgressionWarning, Warning, All);

// Major Equipment Warnings (Equipment not working as intended, flashlight not functioning properly, tools not working as intended, etc)
DECLARE_LOG_CATEGORY_EXTERN(EquipmentWarning, Warning, All);


class HAUNTEDPYRAMID_API DebugLogManager
{
public:
	DebugLogManager();
	~DebugLogManager();
};
