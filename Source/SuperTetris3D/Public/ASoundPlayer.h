// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMODEvent.h"  
#include "FMODAudioComponent.h"
#include "GameFramework/Actor.h"
#include "ASoundPlayer.generated.h"


UCLASS()
class SUPERTETRIS3D_API ASoundPlayer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASoundPlayer();

	// Plays the sound effect for fixing a block into place on the game board.
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayFixBlockSound();

	// Plays the sound effect for clearing a line on the game board.
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayClearLineSound();

	// Plays the sound effect for a player move on the game board.
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayPlayerMoveSound();

	// Plays the ticking sound effect, which may be used for timing or countdowns in the game.
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayTickSound();

	// Plays the sound effect for pressing a button in the game's user interface.
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayPressButtonSound();

	// Plays the background music for the in-game state, providing an immersive audio experience during gameplay.
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayInGameMusic();

	// Plays the background music for the game over state, signaling the end of the game and providing an appropriate audio cue to the player.
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayGameOverMusic();

	// Pauses the currently playing music, allowing for temporary interruptions in the audio without stopping it completely.
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PauseMusic();

	// Resumes the currently paused music, allowing it to continue playing from where it was paused.
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void ResumeMusic();

protected:

	// A helper function to play a given FMOD event, used by the various sound-playing functions to trigger the appropriate sound effects or music.
	void PlaySound(class UFMODEvent* event);

	// FMOD event referencing the sound effect for fixing a block, which can be set in the editor to allow for easy customization of game sounds.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	UFMODEvent* FixBlockEvent;

	// FMOD event referencing the sound effect for clearing a line, which can be set in the editor to allow for easy customization of game sounds.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	UFMODEvent* ClearLineEvent;

	// FMOD event referencing the sound effect for a player move, which can be set in the editor to allow for easy customization of game sounds.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	UFMODEvent* PlayerMoveEvent;

	// FMOD event referencing the ticking sound effect, which can be set in the editor to allow for easy customization of game sounds.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	UFMODEvent* TickEvent;

	// FMOD event referencing the sound effect for pressing a button, which can be set in the editor to allow for easy customization of game sounds.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	UFMODEvent* PressButtonEvent;

	// The FMOD audio component responsible for playing the background music, allowing for control over music playback and properties.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	UFMODAudioComponent* MusicAudioComponent;

	// FMOD event referencing the background music for the in-game state, which can be set in the editor to allow for easy customization of game music.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	UFMODEvent* InGameMusicEvent;

	// FMOD event referencing the background music for the game over state, which can be set in the editor to allow for easy customization of game music.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	UFMODEvent* GameOverMusicEvent;
};
