// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "UScoreWidget.generated.h"

// A user interface widget class for displaying the player's current score and score multiplier in the Super Tetris 3D game.
UCLASS()
class SUPERTETRIS3D_API UScoreWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Score Text inside the VerticalBox
    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreText;

    // Multiplier Text inside the HorizontalBox
    UPROPERTY(meta = (BindWidget))
    UTextBlock* MultiplierText;

    // HorizontalBox container for the multiplier
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* MultiplierSection;
	
    // Sets the displayed score text to the provided `Amount`.
    UFUNCTION(BlueprintCallable, Category = "ScoreUI")
    void SetScore(int Amount);

    // Shows or hides the multiplier UI and updates the multiplier display to `mult`.
    UFUNCTION(BlueprintCallable, Category = "ScoreUI")
    void SetMultiplier(int Amount);

};
