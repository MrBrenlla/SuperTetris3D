// Fill out your copyright notice in the Description page of Project Settings.

#include "AGrid.h"
#include "AFloatingScore.h"

void AGrid::initializeGrid(int width, int height)
{

	gridWidth = width;
	gridHeight = height;

	if (!blocksInGrid.IsEmpty()) blocksInGrid.Empty();

	blocksInGrid.SetNum(width * (height + 5));

	lineCount.SetNum(height + 5);
	for (int j = 0; j < height + 5; j++)
	{
		lineCount[j] = 0;
	}
}

int AGrid::gridIndex(int x, int y)
{
	return y * gridWidth + x;
}

bool AGrid::isEmpty(int x, int y)
{
	return blocksInGrid[gridIndex(x, y)] == nullptr;
}

TArray<int> AGrid::GetFullLines()
{
	TArray<int> fullLines;
	for (int y = 0; y < gridHeight; y++)
	{
		if (lineCount[y] >= gridWidth)
		{
			fullLines.Add(y);
		}
	}
	return fullLines;
}

int AGrid::ClearLines(TArray<int> lines, int mult)
{
	int score = 0;

	for (int line : lines)
	{
		lineCount[line] = 0;

		//UE_LOG(LogTemp, Warning, TEXT("Clearing line %d"), line);
		// Remove blocks in the line
		for (int x = 0; x < gridWidth; x++)
		{
			int index = gridIndex(x, line);
			ABlock* b = blocksInGrid[index];
			if (b != nullptr)
			{
				int s = b->BreackBlock(mult);
				if (score >= 0) {
					score += s;
					blocksInGrid[index] = nullptr;
				}
				else lineCount[line]++; // if score is negative, the block was not destroyed
			}
		}
	}
	return score;
}

TArray<ABlock*> AGrid::FreeLine(int line)
{
	TArray<ABlock*> freedBlocks;
	for (int x = 0; x < gridWidth; x++)
	{
		int index = gridIndex(x, line);
		ABlock* b = blocksInGrid[index];
		if (b != nullptr)
			if (b->MustMove()) {
				freedBlocks.Add(b);
				blocksInGrid[index] = nullptr;
				lineCount[line]--;
			}
	}
	return freedBlocks;
}

void AGrid::FixBlockInGrid(ABlock* block)
{
	int x = block->x;
	int y = block->y;
	//UE_LOG(LogTemp, Warning, TEXT("Fixing block %p in grid at (%d, %d)"), block, x, y);
	blocksInGrid[gridIndex(x, y)] = block;
	lineCount[y] += 1;
}

void AGrid::ResetGrid()
{
	for (int index = 0; index < blocksInGrid.Num(); index++)
	{
		if (blocksInGrid[index]) {
			if (blocksInGrid[index]->SilentDestroy()) {
				blocksInGrid[index] = nullptr;
			}
		}
	}
}





