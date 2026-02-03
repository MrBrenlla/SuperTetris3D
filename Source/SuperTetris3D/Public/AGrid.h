// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASpawner.h"
#include "UScoreWidget.h"
#include "ABlock.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGrid.generated.h"

UCLASS()
class SUPERTETRIS3D_API AGrid : public AActor
{
	GENERATED_BODY()

public: 

	UPROPERTY(BlueprintReadOnly, Category = "GridValues")
	int gridWidth;

	UPROPERTY(BlueprintReadOnly, Category = "GridValues")
	int gridHeight;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void initializeGrid(int width, int height);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool isEmpty(int x, int y);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	TArray<int> GetFullLines();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	int ClearLines(TArray<int> lines, int mult);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	TArray<ABlock*> FreeLine(int line);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void FixBlockInGrid(ABlock* block);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void ResetGrid();


protected:

	UPROPERTY(BlueprintReadOnly, Category = "GridState")
	TArray<ABlock*> blocksInGrid;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	TArray<int> lineCount;

private:
	
	int gridIndex(int x, int y);


};
