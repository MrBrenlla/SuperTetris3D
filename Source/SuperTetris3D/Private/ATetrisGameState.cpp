// Fill out your copyright notice in the Description page of Project Settings.


#include "ATetrisGameState.h"

void ATetrisGameState::RestartData()
{
	mult = 0;
	score = 0;
	UE_LOG(LogTemp, Warning, TEXT("Game data restarted"));
	OnScoreChanged.Broadcast(score);
	OnMultChanged.Broadcast(mult);
}

void ATetrisGameState::AddScore(int scoreToAdd)
{
	score += scoreToAdd;
	UE_LOG(LogTemp, Warning, TEXT("Score is now %lld"), score);
	OnScoreChanged.Broadcast(score);
}

int ATetrisGameState::AddMult(int multToAdd)
{
	mult += multToAdd;
	UE_LOG(LogTemp, Warning, TEXT("Multiplier is now %d"), mult);
	OnMultChanged.Broadcast(mult);
	return mult;
}

void ATetrisGameState::ResetMult()
{
	mult = 0;
	UE_LOG(LogTemp, Warning, TEXT("Multiplier reset to 0"));
	OnMultChanged.Broadcast(mult);
}
