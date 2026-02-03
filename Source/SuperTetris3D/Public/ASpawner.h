// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPieceTemplate.h"
#include "FPiece.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASpawner.generated.h"


UCLASS()
class SUPERTETRIS3D_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawner();

public:

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<UMaterialInterface*> blockMaterials = {};

	UPROPERTY(BlueprintReadWrite, Category = "Spawning")
	UMaterialInterface* goldenMaterial;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<FPieceTemplate> piecesTemplates;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	int gridWidth;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	int gridHeight;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetSpawner(int width, int height, TArray<FPieceTemplate> newPieces);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FPiece SpawnPiece();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void AddBlockMaterials(TArray<UMaterialInterface*> mats);


protected:

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnNextPiece();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void MoveNextPieceToBoard();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<FPiece> pieces;

	FPiece nextPiece;

	void setReserveText();
};
