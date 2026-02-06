// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AWidgetFloatingText.generated.h"

class UWidgetComponent;

// An actor class that represents a floating text widget in the game world, which can be used to display texts in the world when needed. 
UCLASS()
class SUPERTETRIS3D_API AWidgetFloatingText : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AWidgetFloatingText();

	// Sets the text of the UTextBlock in the widget.
	UFUNCTION(BlueprintCallable, Category = "FloatingText")
	void SetText(FText text);


protected:

	// The widget component that contains the floating text widget.
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComp;

};
