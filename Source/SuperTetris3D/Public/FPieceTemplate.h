#pragma once

#include "CoreMinimal.h"
#include "FPieceTemplate.generated.h"

USTRUCT(BlueprintType)
struct FPieceTemplate
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FIntPoint> Blocks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Width = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Height = 0;
};


namespace PieceTemplate
{
    const TArray<FPieceTemplate>& GetDefaults();
}
