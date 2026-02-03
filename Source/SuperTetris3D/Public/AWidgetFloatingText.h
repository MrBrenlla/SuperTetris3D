// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AWidgetFloatingText.generated.h"

class UWidgetComponent;

UCLASS()
class SUPERTETRIS3D_API AWidgetFloatingText : public AActor
{
	GENERATED_BODY()

public:
	AWidgetFloatingText();

	void SetText(FText text);


protected:
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* WidgetComp;

};
