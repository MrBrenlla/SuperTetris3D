// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UTetrisSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTETRIS3D_API UTetrisSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    UPROPERTY()
    bool isLanguageSelected = false;

    UPROPERTY()
    FString SelectedLanguage;

	UPROPERTY()
	TArray<int32> top20HighScores = {};
};
