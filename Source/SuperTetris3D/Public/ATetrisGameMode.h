// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABoard.h"
#include "ATetrisGameMode.generated.h"


UCLASS()
class SUPERTETRIS3D_API ATetrisGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ATetrisGameMode();
	
protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite, Category = "GameModeValues")
	FIntPoint gridDimensions;

	UPROPERTY(EditAnywhere, Category = "GameModeValues")
	TArray<UMaterialInterface*> blockMaterials = {};

	UPROPERTY(EditAnywhere, Category = "GameModeValues")
	UMaterialInterface* goldenMaterial;

	UFUNCTION(BlueprintCallable, Category = "GameModeManagement")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "GameModeManagement")
	void RestartGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameModeManagement")
	void LoseGame();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "GameBoard")
	ABoard* board;

	UPROPERTY(BlueprintReadOnly, Category = "GameSpawner")
	ASpawner* spawner;

	//By default, GameMode don´t run BeginPlay of extended Blueprints.
	// Blueprints that extend this GameMode can implement this event to run custom BeginPlay logic
	UFUNCTION(BlueprintImplementableEvent, Category = "GameModeBlueprintAdaptation")
	void BP_OnBeginPlay();
};



