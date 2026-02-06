// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UTetrisSaveGame.h"
#include "USuperTetris3DGameInstance.generated.h"

// A custom game instance class for the Super Tetris 3D game that manages the player's selected language and high scores using a save game object.
UCLASS()
class SUPERTETRIS3D_API USuperTetris3DGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Initializes the game instance, loading the save game or creating a new one if it doesn't exist.
	virtual void Init() override;

	// Sets the selected language in the save game and persists it.
	UFUNCTION(BlueprintCallable, Category="SuperTetris3D|Localization")
	void SetSelectedLanguage(const FString& Language);

	// Returns the selected language from the save game if chosen, otherwise an empty string.
	UFUNCTION(BlueprintCallable, Category="SuperTetris3D|Localization")
	FString GetSelectedLanguage() const;

	// Adds a new score into the top-20 list, sorts and trims the list, saves it, and returns the index or INDEX_NONE (-1).
	UFUNCTION(BlueprintCallable, Category = "SuperTetris3D|HighScores")
	int SaveHighScore(int32 NewScore);

	// Returns the current top-20 high scores from the save game (or an empty array if unavailable).
	UFUNCTION(BlueprintCallable, Category = "SuperTetris3D|HighScores")
	TArray<int32> GetTop20HighScores() const;

private:

	// The instance of the save game object that holds the player's selected language and high scores.
	UPROPERTY()
	UTetrisSaveGame* TetrisSaveGameInstance;

};
