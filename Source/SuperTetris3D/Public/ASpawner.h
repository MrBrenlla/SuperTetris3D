// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPieceTemplate.h"
#include "FPiece.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASpawner.generated.h"

// An actor class responsible for spawning Tetris pieces in the Super Tetris 3D game, managing piece templates, materials, and the spawning logic for new pieces on the game board.
UCLASS()
class SUPERTETRIS3D_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawner();

public:

	// An array of materials that can be used for the Tetris blocks, allowing for visual variety in the game.
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<UMaterialInterface*> blockMaterials = {};

	// A special material used for the golden block (extra score blocks).
	UPROPERTY(BlueprintReadWrite, Category = "Spawning")
	UMaterialInterface* goldenMaterial;

	// An array of piece templates that define the shapes and configurations of Tetris pieces that can be spawned.
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<FPieceTemplate> piecesTemplates;

	// The width of the Tetris grid.
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int gridWidth;

	// The height of the Tetris grid.
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int gridHeight;

	// Configure spawner with grid size and optional piece templates, instantiates template pieces.
	// If newPieces = {} it will use the last ones used or the default ones if none were used.
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetSpawner(int width, int height, TArray<FPieceTemplate> newPieces);

	// Move the prepared nextPiece onto the board and then spawn a new nextPiece.
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FPiece SpawnPiece();

	// Add additional block materials to the internal pool (by default empty).
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void AddBlockMaterials(TArray<UMaterialInterface*> mats);


protected:

	// Create a new nextPiece instance based on a random template and apply materials (including golden chance).
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnNextPiece();

	// Place the nextPiece at the board start position.
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void MoveNextPieceToBoard();

	// The FPieces that can be spawned.
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<FPiece> pieces;

	// The currently prepared piece that will be moved to the board on the next SpawnPiece() call, and then replaced by a new piece.
	FPiece nextPiece;

	// Spawn a floating "Next piece" label in the world to indicate the reserve.
	void setReserveText();
};
