// Fill out your copyright notice in the Description page of Project Settings.


#include "ATetrisGameMode.h"
#include "ASpawner.h"


ATetrisGameMode::ATetrisGameMode()
{

	gridDimensions = FIntPoint(10, 15);

}

void ATetrisGameMode::BeginPlay()
{
	board = GetWorld()->SpawnActor<ABoard>();

	spawner = GetWorld()->SpawnActor<ASpawner>();

	spawner->SetSpawner(gridDimensions.X, gridDimensions.Y, {});
	spawner->AddBlockMaterials(blockMaterials);
	spawner->goldenMaterial = goldenMaterial;

	UE_LOG(LogTemp, Warning, TEXT("GameMode BeginPlay: Board and Spawner created**********************************************************************************************"));

	BP_OnBeginPlay();

	Super::BeginPlay();

}

void ATetrisGameMode::StartGame()
{
	if (board && spawner)
	{
		board->StartGame(gridDimensions.X, gridDimensions.Y, spawner);;
	}
}

void ATetrisGameMode::RestartGame()
{
	if (board && spawner)
	{
		board->ResetBoard();
		board->StartGame(gridDimensions.X, gridDimensions.Y, spawner);;
	}
}



