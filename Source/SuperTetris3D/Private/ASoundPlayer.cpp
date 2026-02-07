// Fill out your copyright notice in the Description page of Project Settings.


#include "ASoundPlayer.h"
#include "FMODBlueprintStatics.h"              
#include "Components/AudioComponent.h"


// Called when the game starts or when spawned
ASoundPlayer::ASoundPlayer()
{

	MusicAudioComponent = CreateDefaultSubobject<UFMODAudioComponent>(TEXT("MusicComponent"));
	MusicAudioComponent->bAutoActivate = false;
	
}

void ASoundPlayer::PlayFixBlockSound()
{
	PlaySound(FixBlockEvent);
}

void ASoundPlayer::PlayClearLineSound()
{
	PlaySound(ClearLineEvent);
}

void ASoundPlayer::PlayPlayerMoveSound()
{
	PlaySound(PlayerMoveEvent);
}

void ASoundPlayer::PlayTickSound()
{
	PlaySound(TickEvent);
}

void ASoundPlayer::PlayPressButtonSound()
{
	PlaySound(PressButtonEvent);
}

void ASoundPlayer::PlaySound(UFMODEvent* event)
{
	if (event)
	{
		UFMODBlueprintStatics::PlayEvent2D(this, event,true);

	}
}

void ASoundPlayer::PlayInGameMusic()
{
	if (InGameMusicEvent)
	{
		MusicAudioComponent->Stop();
		MusicAudioComponent->SetEvent(InGameMusicEvent);
		MusicAudioComponent->Play();
	}
}

void ASoundPlayer::PlayGameOverMusic()
{
	if (GameOverMusicEvent)
	{
		MusicAudioComponent->Stop();
		MusicAudioComponent->SetEvent(GameOverMusicEvent);
		MusicAudioComponent->Play();
	}
}

void ASoundPlayer::PauseMusic()
{
	MusicAudioComponent->SetPaused(true);
}

void ASoundPlayer::ResumeMusic()
{
	MusicAudioComponent->SetPaused(false);
}


