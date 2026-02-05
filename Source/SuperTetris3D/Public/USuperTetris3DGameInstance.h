// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UTetrisSaveGame.h"
#include "USuperTetris3DGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTETRIS3D_API USuperTetris3DGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category="SuperTetris3D|Localization")
	void SetSelectedLanguage(const FString& Language);

	UFUNCTION(BlueprintCallable, Category="SuperTetris3D|Localization")
	FString GetSelectedLanguage() const;

	UFUNCTION(BlueprintCallable, Category = "SuperTetris3D|HighScores")
	int SaveHighScore(int32 NewScore);

	UFUNCTION(BlueprintCallable, Category = "SuperTetris3D|HighScores")
	TArray<int32> GetTop20HighScores() const;

private:

	UPROPERTY()
	UTetrisSaveGame* TetrisSaveGameInstance;

};
