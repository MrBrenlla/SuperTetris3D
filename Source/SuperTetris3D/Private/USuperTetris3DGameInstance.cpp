// Fill out your copyright notice in the Description page of Project Settings.


#include "USuperTetris3DGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USuperTetris3DGameInstance::Init()
{
	Super::Init();
	if (UGameplayStatics::DoesSaveGameExist(TEXT("TetrisSaveSlot"), 0))
	{
		TetrisSaveGameInstance = Cast<UTetrisSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("TetrisSaveSlot"), 0));
	}
	else
	{
		TetrisSaveGameInstance = Cast<UTetrisSaveGame>(UGameplayStatics::CreateSaveGameObject(UTetrisSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(TetrisSaveGameInstance, TEXT("TetrisSaveSlot"), 0);
	}
}

void USuperTetris3DGameInstance::SetSelectedLanguage(const FString& Language)
{
	if (TetrisSaveGameInstance)
	{
		TetrisSaveGameInstance->isLanguageSelected = true;
		TetrisSaveGameInstance->SelectedLanguage = Language;
		UGameplayStatics::SaveGameToSlot(TetrisSaveGameInstance, TEXT("TetrisSaveSlot"), 0);
	}
}

FString USuperTetris3DGameInstance::GetSelectedLanguage() const
{
	if (TetrisSaveGameInstance && TetrisSaveGameInstance->isLanguageSelected)
	{
		return TetrisSaveGameInstance->SelectedLanguage;
	}
	return FString();
}

// Returns the index of the new score in the top 20 high scores list, or INDEX_NONE if it was not saved
int USuperTetris3DGameInstance::SaveHighScore(int32 NewScore)
{
	if (TetrisSaveGameInstance)
	{

		TetrisSaveGameInstance->top20HighScores.Add(NewScore);
		TetrisSaveGameInstance->top20HighScores.Sort([](int32 A, int32 B) { return A > B; });
		if (TetrisSaveGameInstance->top20HighScores.Num() > 20)
		{
			TetrisSaveGameInstance->top20HighScores.SetNum(20);
		}
		
		UGameplayStatics::SaveGameToSlot(TetrisSaveGameInstance, TEXT("TetrisSaveSlot"), 0);

		return TetrisSaveGameInstance->top20HighScores.Find(NewScore);
	}
	return INDEX_NONE;
}

TArray<int32> USuperTetris3DGameInstance::GetTop20HighScores() const
{
	if (TetrisSaveGameInstance)
	{
		return TetrisSaveGameInstance->top20HighScores;
	}
	return {};
}

