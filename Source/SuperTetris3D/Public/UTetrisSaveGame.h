// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UTetrisSaveGame.generated.h"

// A save game class that stores the player's selected language and the top 20 high scores for the Super Tetris 3D game.
UCLASS()
class SUPERTETRIS3D_API UTetrisSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	
	// Whether the player has selected a language for the game
    UPROPERTY()
    bool isLanguageSelected = false;

	// The selected language for the game, stored as a string (e.g., "en" for English, "es" for Spanish...)
    UPROPERTY()
    FString SelectedLanguage;

	/// The top 20 high scores, sorted in descending order
	UPROPERTY()
	TArray<int32> top20HighScores = {};
};
