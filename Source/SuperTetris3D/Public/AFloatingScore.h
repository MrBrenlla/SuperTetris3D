#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AFloatingScore.generated.h"

class UWidgetComponent;


// An actor class that represents a floating score widget in the game world, which can be used to display scores and multipliers when blocks are broken.
UCLASS()
class SUPERTETRIS3D_API AFloatingScore : public AActor
{
    GENERATED_BODY()

public:
	// Sets default values for this actor's properties
    AFloatingScore();

    // Updates the widget's text to show the provided integer score and schedules auto-destroy.
    void SetScore(int Score);

    // Rotates the widget for multiplier display, sets formatted multiplier text, and schedules auto-destroy.
    void SetMultiplier(int mult);

    // Changes the text color of the widget's TextBlock to the provided FColor.
    void SetColor(FColor color);

protected:

	// The widget component that contains the floating score widget.
    UPROPERTY(VisibleAnywhere)
    UWidgetComponent* WidgetComp;
};