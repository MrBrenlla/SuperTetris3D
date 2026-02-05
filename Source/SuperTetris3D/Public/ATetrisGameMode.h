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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GameModeManagement")
	void RestartGame();

	void RestartGame_Implementation();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameModeManagement")
	void LoseGame();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "GameBoard")
	ABoard* board;

	UPROPERTY(BlueprintReadOnly, Category = "GameSpawner")
	ASpawner* spawner;

};



