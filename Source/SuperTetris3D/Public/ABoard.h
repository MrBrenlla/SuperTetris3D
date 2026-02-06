// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGrid.h"
#include "ABlock.h"
#include "GameFramework/Actor.h"
#include "ABoard.generated.h"


// An actor class that manages the Tetris game board in Super Tetris 3D, handling game logic such as piece movement, line clearing, score updates, and interactions with the grid and spawner to create a cohesive gameplay experience.
UCLASS()
class SUPERTETRIS3D_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	UPROPERTY(EditAnywhere, Category = "GameState")
	float slowFallSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "GameState")
	float fastFallSpeed = 10;

	// The duration of the cooldown period after a horizontal movement, during which the player cannot move the piece again, to prevent excessively fast movements.
	UPROPERTY(EditAnywhere, Category = "GameValues")
	float movementCooldownTime = 0.3;

	// A reference to the spawner actor responsible for creating new Tetris pieces, allowing the board to request new pieces when needed.
	UPROPERTY(EditAnywhere, Category = "Spawner")
	ASpawner* spawner;

	// Initialize grid, set spawner, mark started and set the fall timer.
	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void StartGame(int width, int height, ASpawner* newSpawner);

	// Fix a block into the grid, remove it from moving list and check for game over.
	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void FixBlock(ABlock* block);

	// Move the current piece horizontally if allowed and set a short movement cooldown.
	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void MoveBlock(float dir);

	// Rotate the current piece around its center if the rotated positions are valid and free.
	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void RotateBlock(float dir);

	// Restore slow fall speed and schedule the next fall tick.
	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void setSlowSpeed();

	// Set fast fall speed and immediately perform a game action.
	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void setFastSpeed();

	// Reset the board state, destroy any moving blocks, and reset game state counters.
	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void ResetBoard();

protected:

	// A list of currently moving blocks that are part of the active piece or falling lines.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	TArray<ABlock*> movingBlocks;

	// A flag indicating whether the player can currently move the active piece.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	bool playerCanMove;

	// A flag indicating whether the active piece is currently in a cooldown period after a horizontal movement, preventing further movement until the cooldown expires.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	bool movementInCooldown = false;

	// The horizontal range of the moving blocks, used for validating horizontal movements and rotations.
	// This range is only valid when the moving pieces were spawned by the spawner, never while they are falling lines or part of the piece has allready been fixed.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	FIntPoint movingBlocksRangeX;

	// The vertical range of the moving blocks, used for validating vertical movements and rotations.
	// This range is only valid when the moving pieces were spawned by the spawner, never while they are falling lines or part of the piece has allready been fixed.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	FIntPoint movingBlocksRangeY;

	// A reference to the grid actor that represents the Tetris grid.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	AGrid* grid;

	// The current fall speed multiplier, which can be modified by player input to slow down or speed up the falling of pieces.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	float actualFallSpeed;

	//The number of pieces that have been spawned so far, used for tracking game progress and speed scaling.
	UPROPERTY(EditAnywhere, Category = "GameState")
	int pieceCount = 0;

	// The base time interval for pieces to fall one row, which can be modified by the actualFallSpeed multiplier to adjust the falling speed dynamically.
	// This value is used to schedule the next fall tick in the game loop, and can be adjusted based on the number of pieces spawned for increasing difficulty.
	UPROPERTY(EditAnywhere, Category = "GameValues")
	float fallTime = 0.8;

	// A flag indicating whether the game has started, used to control the flow of the game loop and prevent actions before the game is initialized.
	bool gameStarted = false;

	// Timer handles for managing the scheduling of game actions and movement cooldowns, allowing for precise control over the timing of game events and player input restrictions.
	FTimerHandle movementCooldownTimerHandle;

	// Timer handle for scheduling the next fall tick in the game loop, which controls the regular falling of pieces and can be adjusted for speed changes.
	FTimerHandle fallTimerHandle;

	// Number of consecutive times that the player has cleared any line by chain reactions. 
	// This is used to calculate the score multiplier for line clears, rewarding players for making chain reactions and clearing multiple lines in succession.
	// This counter does not count if multiple lines are cleared at once, only if a line clear causes another line to be cleared by the falling blocks.
	int consecutiveMult;

	// Core loop step, spawn if needed, move blocks down, find lines, and schedule next tick.
	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void GameAction();

	// Stop the game and notify the GameMode that the player has lost.
	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void LoseGame();

	// Spawn a new piece from the spawner and add its blocks to the moving list.
	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void SpawnBlocks();

	// Attempt to move all moving blocks one row down, stopping those that collide or reach bottom.
	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void MoveBlocksDown();

	// Detect and clear completed lines, update score/multiplier and show floating scores. 
	// Then allow all blocks to fall if any lines were cleared.
	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void FindLines();

	// Collect freed blocks from every row into the moving blocks list.
	void AllowMovingLines();

	// Spawn a floating score actor to display the multiplier at the given line.
	void ShowMultiplier(int line, int mult);

	// Re-enable player lateral movement after the cooldown period.
	void AllowMovementAfterCooldown();
	
};
