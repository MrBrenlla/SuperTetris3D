// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGrid.h"
#include "ABlock.h"
#include "GameFramework/Actor.h"
#include "ABoard.generated.h"

UCLASS()
class SUPERTETRIS3D_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	UPROPERTY(EditAnywhere, Category = "GameValues")
	float SpeedMultiplier = 80;

	UPROPERTY(EditAnywhere, Category = "GameValues")
	float movementCooldownTime = 0.3;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	ASpawner* spawner;

	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void StartGame(int width, int height, ASpawner* newSpawner);

	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void FixBlock(ABlock* block);

	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void SpawnBlocks();

	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void MoveBlocksDown();

	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void FindLines();

	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void MoveBlock(float dir);

	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void RotateBlock(float dir);

	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void setSlowSpeed();

	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void setFastSpeed();

	UFUNCTION(BlueprintCallable, Category = "GameInputs")
	void ResetBoard();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	TArray<ABlock*> movingBlocks;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	bool playerCanMove;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	bool movementInCooldown = false;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	FIntPoint movingBlocksRangeX;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	FIntPoint movingBlocksRangeY;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	AGrid* grid;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	float actualFallSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "GameState")
	float slowFallSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "GameState")
	float fastFallSpeed = 10;

	UPROPERTY(EditAnywhere, Category = "GameState")
	int pieceCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ScoreUI")
	UScoreWidget* scoreWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ScoreUI")
	TSubclassOf<UScoreWidget> scoreWidgetClass;

	UPROPERTY(EditAnywhere, Category = "GameValues")
	float fallTime = 0.8;

	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void GameAction();

	UFUNCTION(BlueprintCallable, Category = "GameOrders")
	void LoseGame();

private:
	bool gameStarted = false;
	void AllowMovingLines();
	void ShowMultiplier(int line, int mult);
	void AllowMovementAfterCooldown();
	FTimerHandle movementCooldownTimerHandle;
	FTimerHandle fallTimerHandle;

	int consecutiveMult;
};
