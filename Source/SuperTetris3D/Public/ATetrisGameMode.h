// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABoard.h"
#include "ATetrisGameMode.generated.h"

// A custom GameMode class for the Super Tetris 3D game, responsible for managing the overall game state and setting game values.
UCLASS()
class SUPERTETRIS3D_API ATetrisGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	// Sets default values for this game mode's properties
	ATetrisGameMode();
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// The dimensions of the Tetris grid, represented as an FIntPoint where X is the width and Y is the height of the grid.
	UPROPERTY(BlueprintReadWrite, Category = "GameModeValues")
	FIntPoint gridDimensions;

	//An array of materials that can be used for the Tetris blocks, allowing for visual variety in the game.
	UPROPERTY(EditAnywhere, Category = "GameModeValues")
	TArray<UMaterialInterface*> blockMaterials = {};

	// A special material used for the golden block (extra score blocks).
	UPROPERTY(EditAnywhere, Category = "GameModeValues")
	UMaterialInterface* goldenMaterial;

	// Starts the Tetris game by initializing the board with the configured grid size and spawner.
	UFUNCTION(BlueprintCallable, Category = "GameModeManagement")
	void StartGame();

	// Resets the game board to its initial state when a restart is requested.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GameModeManagement")
	void RestartGame();

	// Default implementation of RestartGame, which can be overridden in Blueprints for additional behavior on game restart.
	void RestartGame_Implementation();
	
	// Triggers the lose game event, which can be implemented in Blueprints to handle game over logic and UI.
	UFUNCTION(BlueprintImplementableEvent, Category = "GameModeManagement")
	void LoseGame();

protected:

	// A reference to the game board actor, which manages the Tetris grid and block placements.
	UPROPERTY(BlueprintReadOnly, Category = "GameBoard")
	ABoard* board;

	// A reference to the spawner actor, which is responsible for spawning new Tetris pieces into the game.
	UPROPERTY(BlueprintReadOnly, Category = "GameSpawner")
	ASpawner* spawner;

};



