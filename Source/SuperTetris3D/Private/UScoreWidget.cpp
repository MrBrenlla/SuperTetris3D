// Fill out your copyright notice in the Description page of Project Settings.


#include "UScoreWidget.h"

void UScoreWidget::SetScore(int Amount) {

	UE_LOG(LogTemp, Warning, TEXT("Setting score to %d"), Amount);
	ScoreText->SetText(FText::AsNumber(Amount));

}


void UScoreWidget::SetMultiplier(int mult) {

	if (mult < 1) {
		UE_LOG(LogTemp, Warning, TEXT("Removing multiplier"));
		MultiplierSection->SetVisibility(ESlateVisibility::Collapsed);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Setting multiplier to x%d"), mult);
		MultiplierSection->SetVisibility(ESlateVisibility::Visible);
		MultiplierText->SetText(FText::Format(FText::FromString("x{0}"), mult));
	}

}