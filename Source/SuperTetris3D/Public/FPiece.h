#pragma once

#include "CoreMinimal.h"
#include "ABlock.h"
#include "FPiece.generated.h"

USTRUCT(BlueprintType)
struct FPiece
{
    GENERATED_BODY()

    // Lista de bloques
    UPROPERTY()
    TArray<ABlock*> Blocks = {};

    // Límites
    UPROPERTY()
    int MinX = 0;

    UPROPERTY()
    int MaxX = 0;

    UPROPERTY()
    int MinY = 0;

    UPROPERTY()
    int MaxY = 0;
};
