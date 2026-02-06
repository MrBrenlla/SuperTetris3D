// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASpawner.h"
#include "UScoreWidget.h"
#include "ABlock.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGrid.generated.h"


// An actor class that represents the Tetris grid in the Super Tetris 3D game, responsible for managing the grid state, block placements, line clearing, and score calculations based on the current configuration of blocks on the grid.
UCLASS()
class SUPERTETRIS3D_API AGrid : public AActor
{
	GENERATED_BODY()

public: 

	//The grid width, representing the number of columns in the Tetris grid.
	UPROPERTY(BlueprintReadOnly, Category = "GridValues")
	int gridWidth;

	//The grid height, representing the number of rows in the Tetris grid.
	UPROPERTY(BlueprintReadOnly, Category = "GridValues")
	int gridHeight;

	// Initializes the grid dimensions and allocates internal arrays.
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void initializeGrid(int width, int height);

	// Returns true if the cell at (x, y) has no block.
	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool isEmpty(int x, int y);

	// Scans and returns a list of fully occupied line indices.
	UFUNCTION(BlueprintCallable, Category = "Grid")
	TArray<int> GetFullLines();

	// Clears the specified lines, destroys blocks and returns the score gained.
	UFUNCTION(BlueprintCallable, Category = "Grid")
	int ClearLines(TArray<int> lines, int mult);

	// Frees movable blocks from a line and returns them.
	UFUNCTION(BlueprintCallable, Category = "Grid")
	TArray<ABlock*> FreeLine(int line);

	// Fixes a block into the internal grid storage and updates the line count.
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void FixBlockInGrid(ABlock* block);

	// Destroys any remaining blocks silently and clears their references.
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void ResetGrid();


protected:

	// An array representing the grid cells, where each cell can hold a reference to a block or be null if empty.
	UPROPERTY(BlueprintReadOnly, Category = "GridState")
	TArray<ABlock*> blocksInGrid;

	// An array that keeps track of how many blocks are in each line, used for quickly identifying full lines.
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	TArray<int> lineCount;
	
	// Computes the 1D array index for coordinates (x, y).
	UFUNCTION(BlueprintCallable, Category = "Grid")
	int gridIndex(int x, int y);


};
