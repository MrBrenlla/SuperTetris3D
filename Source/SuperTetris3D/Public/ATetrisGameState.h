// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h" 
#include "UObject/ObjectMacros.h"          
#include "GameFramework/GameStateBase.h"
#include "ATetrisGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMultChanged, int, mult);


UCLASS()
class SUPERTETRIS3D_API ATetrisGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnMultChanged OnMultChanged;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	int mult=0;

	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnScoreChanged;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	int score=0;
	
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void RestartData();

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void AddScore(int scoreToAdd);

	UFUNCTION(BlueprintCallable, Category = "GameState")
	int AddMult(int multToAdd);

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void ResetMult();
};
