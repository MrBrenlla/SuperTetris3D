#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AFloatingScore.generated.h"

class UWidgetComponent;

UCLASS()
class SUPERTETRIS3D_API AFloatingScore : public AActor
{
    GENERATED_BODY()

public:
    AFloatingScore();

    void SetScore(int Score);

    void SetMultiplier(int mult);

	void SetColor(FColor color);

protected:
    UPROPERTY(VisibleAnywhere)
    UWidgetComponent* WidgetComp;
};