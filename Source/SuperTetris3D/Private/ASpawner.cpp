// Fill out your copyright notice in the Description page of Project Settings.

#include "ASpawner.h"
#include "FPiece.h"
#include "FPieceTemplate.h"
#include "AWidgetFloatingText.h"
#include "Internationalization/Text.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	if (piecesTemplates.Num() == 0) this->piecesTemplates = PieceTemplate::GetDefaults();
	
}

void ASpawner::SetSpawner(int width, int height, TArray<FPieceTemplate> newPieces = {})
{
	gridWidth = width;
	gridHeight = height;

	if (newPieces.Num() != 0) this->piecesTemplates = newPieces;

	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("Can`t set spawner: World is null"));
		return;
	};

	setReserveText();

	for (FPieceTemplate templatePiece : piecesTemplates) {

		FPiece newPiece = FPiece();

		newPiece.MaxX = -3 - ((5 - templatePiece.Width)/2);
		newPiece.MinX = newPiece.MaxX - templatePiece.Width +1;
		newPiece.MaxY = gridHeight;
		newPiece.MinY = newPiece.MaxY-templatePiece.Height +1;
		
		for (FIntPoint blockPos : templatePiece.Blocks)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Create block"));

			ABlock* b = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass());

			if (b)
			{
				b->SetActorHiddenInGame(true);

				int x = newPiece.MinX + blockPos.X;
				int y = newPiece.MinY + blockPos.Y;
				b->SetXY(x, y);

				for (ABlock* posibleConected : newPiece.Blocks) {
					int x2 = posibleConected->x;
					int y2 = posibleConected->y;
					if (((x2 == x + 1 || x2 == x - 1) && y2 == y)||
						((y2 == y + 1 || y2 == y - 1) && x2 == x))
					{
						//UE_LOG(LogTemp, Warning, TEXT("Conected block"));
						b->ConectBlock(posibleConected);
					}
				}

				//UE_LOG(LogTemp, Warning, TEXT("Block Created"));

				newPiece.Blocks.Add(b);
			}
		}
		pieces.Add(newPiece);
	}

	SpawnNextPiece();

}

void ASpawner::setReserveText()
{
	if (UWorld* World = GetWorld())
	{
		int x = (5) * 100;
		int y = (gridHeight + 2) * 100;

		AWidgetFloatingText* textActor = World->SpawnActor<AWidgetFloatingText>(
			AWidgetFloatingText::StaticClass(),
			FVector(0,x,y),
			FRotator::ZeroRotator
		);

		if (textActor)
		{

			FText text = NSLOCTEXT("InGame", "Next piece:", "Next piece:");

			textActor->SetText(text);
		}
	}
}

FPiece ASpawner::SpawnPiece() {

	MoveNextPieceToBoard();
	FPiece toReturn = nextPiece;

	SpawnNextPiece();

	return toReturn;
}

void ASpawner::SpawnNextPiece()
{

	if (!GetWorld())
	{
		UE_LOG(LogTemp, Error, TEXT("Can`t spawn block: World is null"));
		nextPiece = FPiece();
		return;
	};

	bool isGoldenPiece = (FMath::RandRange(0, 19) == 0); //5% chance

	FPiece reference = pieces[FMath::RandRange(0, pieces.Num() - 1)];

	nextPiece = FPiece();

	nextPiece.MaxX = reference.MaxX;
	nextPiece.MinX = reference.MinX;
	nextPiece.MaxY = reference.MaxY;
	nextPiece.MinY = reference.MinY;

	UMaterialInterface* mat = nullptr;
	if(isGoldenPiece) mat = goldenMaterial;
	else if (blockMaterials.Num() != 0) mat = blockMaterials[FMath::RandRange(0, blockMaterials.Num() - 1)];

	TMap<ABlock*, ABlock*> oldToNew;

	for (ABlock* b : reference.Blocks) {

		//UE_LOG(LogTemp, Warning, TEXT("Create block"));

		ABlock* newBlock = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass());

		if (newBlock)
		{
			int x = b->x;
			int y = b->y;
			newBlock->SetXY(x, y);

			oldToNew.Add(b, newBlock);

			for (ABlock* conected : b->conectedBlocks) {
				ABlock** newConected = oldToNew.Find(conected);
				if (newConected!=nullptr)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Conected spawned block"));
					newBlock->ConectBlock(*newConected);
				}
			}

			//UE_LOG(LogTemp, Warning, TEXT("Block Created"));
			if (mat != nullptr) {
				newBlock->SetMaterial(mat);
				if (isGoldenPiece) newBlock->SetGolden();
			}
			nextPiece.Blocks.Add(newBlock);
		}
	}
}

void ASpawner::MoveNextPieceToBoard() {

	int width = nextPiece.MaxX - nextPiece.MinX + 1;
	int height = nextPiece.MaxY - nextPiece.MinY + 1;

	int oldMinX = nextPiece.MinX;
	int oldMinY = nextPiece.MinY;

	int startX = (gridWidth - width) / 2;
	int startY = gridHeight + 1;

	nextPiece.MinX = startX;
	nextPiece.MaxX = startX + width - 1;
	nextPiece.MinY = startY;
	nextPiece.MaxY = startY + height - 1;

	for (ABlock* b : nextPiece.Blocks) {
		int x = b->x - oldMinX + startX;
		int y = b->y - oldMinY + startY;
		b->SetXY(x, y);
		b->SetActorHiddenInGame(false);
	}

}

void ASpawner::AddBlockMaterials(TArray<UMaterialInterface*> mats)
{
	blockMaterials.Append(mats);
}

