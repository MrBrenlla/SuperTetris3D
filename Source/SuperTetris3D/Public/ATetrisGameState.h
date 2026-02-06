// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h" 
#include "UObject/ObjectMacros.h"          
#include "GameFramework/GameStateBase.h"
#include "ATetrisGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMultChanged, int, mult);

// A custom GameState class for the Super Tetris 3D game, responsible for managing the player's score and score multiplier, and broadcasting changes to these values through BlueprintAssignable events.
UCLASS()
class SUPERTETRIS3D_API ATetrisGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	// Multiplier change event that can be bound to in Blueprints to react to changes in the multiplier value.
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnMultChanged OnMultChanged;

	// The current score multiplier.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	int mult=0;

	// Score change event that can be bound to in Blueprints to react to changes in the score value.
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnScoreChanged;

	// The current score.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	int score=0;
	
	// Resets runtime score and multiplier to zero and broadcasts the changes.
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void RestartData();

	// Adds the specified amount to the current score and broadcasts the new score.
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void AddScore(int scoreToAdd);

	// Increments the multiplier by the given amount, broadcasts the new multiplier, and returns it.
	UFUNCTION(BlueprintCallable, Category = "GameState")
	int AddMult(int multToAdd);

	// Resets the multiplier to zero and broadcasts the change.
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void ResetMult();
};
