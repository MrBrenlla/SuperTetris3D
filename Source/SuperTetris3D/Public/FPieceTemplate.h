#pragma once

#include "CoreMinimal.h"
#include "FPieceTemplate.generated.h"


// A struct that defines the template for a Tetris piece, including its shape and dimensions, which can be used to spawn pieces in the game.
USTRUCT(BlueprintType)
struct FPieceTemplate
{
    GENERATED_BODY()

	// The blocks that make up the piece, represented as an array of integer points (x, y) relative to the piece's origin.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FIntPoint> Blocks;

	// The width of the piece's bounding box, used for placement and collision detection.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Width = 0;

	// The height of the piece's bounding box, used for placement and collision detection.
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Height = 0;
};


namespace PieceTemplate
{
	// Returns the default piece templates for the game.
	UFUNCTION(BlueprintCallable, Category = "PieceTemplate")
    const TArray<FPieceTemplate>& GetDefaults();
}
