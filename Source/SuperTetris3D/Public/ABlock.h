// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABlock.generated.h"

class ABoard;

// An actor class that represents an individual block in the Super Tetris 3D game, responsible for managing its position, movement state, connections to other blocks, and interactions with the game board and grid to facilitate gameplay mechanics such as piece movement, line clearing, and scoring.
UCLASS()
class SUPERTETRIS3D_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	
	// X coordinate of the block in the grid, used for positioning and movement logic.
	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	int32 x;

	// Y coordinate of the block in the grid, used for positioning and movement logic.
	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	int32 y;

	// The static mesh used for this block, which can be set in the editor and applied to the block's mesh component.
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	UStaticMesh* DefaultMesh;

	// Set of blocks that are connected to this block (part of the same piece).
	// This conection is bidirectional, so if block A is connected to block B, block B is also connected to block A. 
	// Used for propagating movements and actions across all blocks of a piece.
	UPROPERTY(BlueprintReadOnly, Category = "BlockConectedBlocks")
	TSet<ABlock*> conectedBlocks;

	// Make the block non-movable and stop any movement state.
	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void MakeStatic();

	// Set grid coordinates X/Y and update actor world location accordingly.
	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void SetXY(int32 newX, int32 newY);

	// Stop this block's movement, fix it on the board, and propagate to connected blocks.
	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void StopMovement(ABoard* gameMode);

	// Mark the block as moving if it is movable; return whether it must move.
	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual bool MustMove();

	// Detachs connections, destroys actor and returns and shows score.
	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual int BreackBlock(int mult);

	// Connect this block with another block bidirectionally if both are movable.
	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void ConectBlock(ABlock* block);

	// Set the block's material on its mesh component.
	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void SetMaterial(UMaterialInterface* mat);

	// Mark this block as a golden block (affects scoring).
	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void SetGolden();

	/* Destroy the actor silently (without scoring and conectiong removing) only if it is movable; used when clearing many blocks.
	Use only if all blocs are going to be removed, to avoid errors with conected blocks*/
	UFUNCTION(BlueprintCallable, Category = "Block")
	bool SilentDestroy();

protected:

	// Spawn a floating score actor at this block's location and return the points awarded.
	UFUNCTION(BlueprintCallable, Category = "Block")
	int ShowScore(int mult);

	// A flag indicating whether the block can be moved.
	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	bool movable = true;

	// The static mesh component used to render this block.
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* blockMesh;

	// A flag indicating whether the block is currently moving (part of an active piece or falling line).
	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	bool isMoving;

	// A flag indicating whether the block is golden, which affects scoring when the block is cleared.
	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	bool isGolden;

};
