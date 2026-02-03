// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABlock.generated.h"

class ABoard;

UCLASS()
class SUPERTETRIS3D_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	//position in the grid
	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	int32 x;

	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	int32 y;

	UPROPERTY(EditDefaultsOnly, Category = "Block")
	UStaticMesh* DefaultMesh;

	UPROPERTY(BlueprintReadOnly, Category = "BlockConectedBlocks")
	TSet<ABlock*> conectedBlocks;

	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void MakeStatic();

	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void SetXY(int32 newX, int32 newY);

	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void StopMovement(ABoard* gameMode);

	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual bool MustMove();

	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual int BreackBlock(int mult);

	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void ConectBlock(ABlock* block);

	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void SetMaterial(UMaterialInterface* mat);

	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual void SetGolden();

	UFUNCTION(BlueprintCallable, Category = "Block")
	bool SilentDestroy();

protected:
	//Atributes

	UFUNCTION(BlueprintCallable, Category = "Block")
	int ShowScore(int mult);

	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	bool movable = true;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* blockMesh;

	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	bool isMoving;

	UPROPERTY(BlueprintReadOnly, Category = "BlockState")
	bool isGolden;

};
