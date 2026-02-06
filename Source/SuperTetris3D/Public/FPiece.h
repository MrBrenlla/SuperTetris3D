#pragma once

#include "CoreMinimal.h"
#include "ABlock.h"
#include "FPiece.generated.h"


// The FPiece struct represents a Tetris piece, which is composed of multiple ABlock actors. It includes properties for the blocks that make up the piece and their bounding coordinates for placement and collision detection.
// The conection between the blocks in a piece is managed through the ABlock actors themselves, which can be connected to each other using their conectedBlocks property, wich should be set manually when creating the piece (the spawner should do it when spawning the piece). 
// The FPiece struct is primarily used for managing the collection of blocks that form a piece and their spatial properties, while the ABlock actors handle the individual block behavior and connections.
USTRUCT(BlueprintType)
struct FPiece
{
    GENERATED_BODY()

	// The blocks that make up the piece, represented as an array of pointers to ABlock actors.
    UPROPERTY()
    TArray<ABlock*> Blocks = {};

	// The minimum X coordinate of the blocks in the piece, used for placement and collision detection.
    UPROPERTY()
    int MinX = 0;

	// The maximum X coordinate of the blocks in the piece, used for placement and collision detection.
    UPROPERTY()
    int MaxX = 0;

	// The minimum Y coordinate of the blocks in the piece, used for placement and collision detection.
    UPROPERTY()
    int MinY = 0;

	// The maximum Y coordinate of the blocks in the piece, used for placement and collision detection.
    UPROPERTY()
    int MaxY = 0;
};
