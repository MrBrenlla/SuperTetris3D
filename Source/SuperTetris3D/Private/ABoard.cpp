// Fill out your copyright notice in the Description page of Project Settings.


#include "ABoard.h"
#include "AGrid.h"
#include "ABlock.h"
#include "AFloatingScore.h"
#include "ATetrisGameState.h"
#include "ATetrisGameMode.h"
#include "FMODBlueprintStatics.h"

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = true;

	playerCanMove = true;

	consecutiveMult = 0;

	actualFallSpeed = slowFallSpeed;
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();

	grid = GetWorld()->SpawnActor<AGrid>();

	ATetrisGameState* GS = GetWorld()->GetGameState<ATetrisGameState>();
	if (GS)
	{
		GS->RestartData();
	}

}

void ABoard::StartGame(int width, int height, ASpawner* newSpawner)
{
	grid->initializeGrid(width, height);

	spawner = newSpawner;

	gameStarted = true;

	UFMODBlueprintStatics::SetGlobalParameterByName("PitchModification", 1);

	GetWorld()->GetTimerManager().SetTimer(
		fallTimerHandle,
		this,
		&ABoard::GameAction,
		(fallTime * pow(0.95, pieceCount / 15)) / actualFallSpeed,
		false
	);
}

void ABoard::GameAction()
{
	actualTickSound = 0;

	if (movingBlocks.IsEmpty()) SpawnBlocks();

	MoveBlocksDown();

	if (movingBlocks.IsEmpty()) FindLines();


	switch (actualTickSound)
	{
	case 0:
		soundPlayer->PlayTickSound();
		break;
	case 1:
		soundPlayer->PlayFixBlockSound();
		break;
	case 2:
		soundPlayer->PlayClearLineSound();
		break;
	default:
		break;
	}

	float speedMultiplier = pow(0.95, static_cast<float>(pieceCount) / 15.f);

	UFMODBlueprintStatics::SetGlobalParameterByName("PitchModification", speedMultiplier);

	if (gameStarted)
		GetWorld()->GetTimerManager().SetTimer(
			fallTimerHandle,
			this,
			&ABoard::GameAction,
			fallTime * speedMultiplier / actualFallSpeed,
			false
		);
}

void ABoard::SpawnBlocks() {

	if (consecutiveMult == 0) {
		ATetrisGameState* GS = GetWorld()->GetGameState<ATetrisGameState>();
		if (GS)
		{
			GS->ResetMult();
		}
	}
	consecutiveMult = 0;
	playerCanMove = true;

	UE_LOG(LogTemp, Warning, TEXT("Spawned"));

	FPiece newPiece = spawner->SpawnPiece();

	if (newPiece.Blocks.IsEmpty()) return;

	movingBlocks.Append(newPiece.Blocks);

	movingBlocksRangeX = FIntPoint(newPiece.MinX, newPiece.MaxX);
	movingBlocksRangeY = FIntPoint(newPiece.MinY, newPiece.MaxY);

	pieceCount++;
}

void ABoard::MoveBlocksDown()
{

	TArray<ABlock*> blocksToMove = movingBlocks;

	for (ABlock* b : blocksToMove)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Try moving block %p:"),b);
		int x = b->x;
		int y = b->y;
		if (y <= 0) {
			//UE_LOG(LogTemp, Warning, TEXT("--End Line--"));
			b->StopMovement(this);
			actualTickSound = 1;
		}
		else if (!grid->isEmpty(x, y - 1)) {
			//UE_LOG(LogTemp, Warning, TEXT("--Block under--"));
			b->StopMovement(this);
			actualTickSound = 1;
		}
		//else UE_LOG(LogTemp, Warning, TEXT("--OK, can move--"));
	}

	for (ABlock* b : movingBlocks)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Moving block %p:"), b);
		b->SetXY(b->x, b->y - 1);
	}

	movingBlocksRangeY.X -= 1;
	movingBlocksRangeY.Y -= 1;

}

void ABoard::FindLines()
{

	playerCanMove = false;

	TArray<int> completedLines = grid->GetFullLines();


	if (completedLines.IsEmpty()) return;

	actualTickSound = 2;

	int newMult = completedLines.Num() * pow(2, consecutiveMult);
	consecutiveMult++;

	ATetrisGameState* GS = GetWorld()->GetGameState<ATetrisGameState>();
	if (GS)
	{
		newMult = GS->AddMult(newMult);
	}

	int newScore = grid->ClearLines(completedLines, newMult);

	if (GS)
	{
		GS->AddScore(newScore);
	}

	for (int l : completedLines)
	{
		ShowMultiplier(l, newMult);
	}

	AllowMovingLines();
}



void ABoard::AllowMovingLines()
{

	for (int j = 0; j < grid->gridHeight; j++)
	{
		movingBlocks.Append(grid->FreeLine(j));
	}
}

void ABoard::ShowMultiplier(int line, int mult)
{
	FVector SpawnPos = FVector(0, -100 * (grid->gridWidth + 1), 100 * line);

	if (UWorld* World = GetWorld())
	{

		AFloatingScore* ScoreActor = World->SpawnActor<AFloatingScore>(
			AFloatingScore::StaticClass(),
			SpawnPos,
			FRotator::ZeroRotator
		);

		if (ScoreActor)
		{
			ScoreActor->SetMultiplier(mult);
		}
	}

}

void ABoard::MoveBlock(float dir)
{

	if (!gameStarted) return;

	if (dir > 0.5) dir = 1;
	else if (dir < -0.5) dir = -1;
	else return;

	//UE_LOG(LogTemp, Warning, TEXT("Wanting to move %f"), dir);
	if (!playerCanMove || movementInCooldown) return;

	UE_LOG(LogTemp, Warning, TEXT("Trying to move %d with max %d"), movingBlocksRangeX.Y, grid->gridWidth - 1);

	if (dir < 0 && movingBlocksRangeX.X <= 0) return;
	if (dir > 0 && movingBlocksRangeX.Y >= grid->gridWidth - 1) return;
	for (ABlock* b : movingBlocks)
	{
		int newX = b->x + dir;
		if (!grid->isEmpty(newX, b->y)) return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Moving"));
	for (ABlock* b : movingBlocks)
	{
		int newX = b->x + dir;
		b->SetXY(newX, b->y);
	}

	movingBlocksRangeX.X += dir;
	movingBlocksRangeX.Y += dir;

	movementInCooldown = true;

	GetWorld()->GetTimerManager().SetTimer(
		movementCooldownTimerHandle,
		this,
		&ABoard::AllowMovementAfterCooldown,
		movementCooldownTime,
		false
	);

	soundPlayer->PlayPlayerMoveSound();
}

void ABoard::AllowMovementAfterCooldown()
{
	movementInCooldown = false;
}

void ABoard::RotateBlock(float dir)
{

	if (!gameStarted) return;

	if (!playerCanMove) return;

	TMap<ABlock*, FIntPoint> newPos;


	int auxSum = movingBlocksRangeY.X + movingBlocksRangeY.Y;

	if (dir < 0) auxSum++; // to handle odd height ranges correctly

	int midX = (movingBlocksRangeX.X + movingBlocksRangeX.Y) / 2;
	int midY = (auxSum) / 2;;
	int minX = movingBlocksRangeX.X;
	int minY = movingBlocksRangeY.X;
	int maxY = movingBlocksRangeY.Y;
	int xRange = movingBlocksRangeX.Y - movingBlocksRangeX.X;

	//UE_LOG(LogTemp, Warning, TEXT("midX:%d, midY:%d, minX:%d, minY:%d, maxY:%d, xRannge:%d"), midX, midY,minX,minY,maxY,xRange);

	for (ABlock* b : movingBlocks)
	{
		int relX = b->x - minX;

		FIntPoint p;
		if (dir < 0) {

			p.X = midX + (midY - b->y);
			p.Y = minY + relX;

		}
		else {

			p.X = midX + (b->y - midY);
			p.Y = minY + (xRange - relX);
		}

		//UE_LOG(LogTemp, Warning, TEXT("---relX:%d\n (%d, %d) -> (%d, %d)"),relX,b->x,b->y,p.X,p.Y);

		if (p.X < 0 || p.X >= grid->gridWidth)return;
		if (p.Y < 0 || p.Y >= grid->gridHeight + 5)return;
		if (!grid->isEmpty(p.X, p.Y)) return;
		newPos.Add(b, p);
	}

	for (const TPair<ABlock*, FIntPoint>& Pair : newPos)
	{
		ABlock* b = Pair.Key;
		const FIntPoint& p = Pair.Value;

		b->SetXY(p.X, p.Y);
	}

	movingBlocksRangeY.Y = minY + xRange;
	if (dir < 0) {
		movingBlocksRangeX.X = midX + (midY - maxY);
		movingBlocksRangeX.Y = midX + (midY - minY);
	}
	else {
		movingBlocksRangeX.X = midX + (minY - midY);
		movingBlocksRangeX.Y = midX + (maxY - midY);
	}

	soundPlayer->PlayPlayerMoveSound();

}

void ABoard::setFastSpeed()
{
	if (!gameStarted) return;

	actualFallSpeed = fastFallSpeed;

	GetWorld()->GetTimerManager().ClearTimer(fallTimerHandle);

	GameAction();
}

void ABoard::ResetBoard()
{

	pieceCount = 0;

	actualFallSpeed = slowFallSpeed;

	grid->ResetGrid();

	for (ABlock* b : movingBlocks)
	{
		if (b)
		{
			b->Destroy();
		}
	}
	movingBlocks.Empty();

	UFMODBlueprintStatics::SetGlobalParameterByName("PitchModification", 1);

	ATetrisGameState* GS = GetWorld()->GetGameState<ATetrisGameState>();
	if (GS)
	{
		GS->RestartData();
	}

}

void ABoard::setSlowSpeed()
{

	if (!gameStarted) return;

	actualFallSpeed = slowFallSpeed;
	GetWorld()->GetTimerManager().ClearTimer(fallTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(
		fallTimerHandle,
		this,
		&ABoard::GameAction,
		(fallTime * pow(0.95, pieceCount / 15)) / actualFallSpeed,
		false
	);
}

void ABoard::FixBlock(ABlock* block)
{
	grid->FixBlockInGrid(block);
	movingBlocks.Remove(block);
	if (block->y >= grid->gridHeight && gameStarted)
	{
		LoseGame();
	}
}

void ABoard::LoseGame() {

	gameStarted = false;

	GetWorld()->GetTimerManager().ClearTimer(fallTimerHandle);

	ATetrisGameMode* GS = GetWorld()->GetAuthGameMode<ATetrisGameMode>();
	if (GS)
	{
		GS->LoseGame();
	}
}

void ABoard::PauseGame()
{
	if (!gameStarted || gameIsPaused) return;
	gameIsPaused = true;

	if (GetWorld()->GetTimerManager().TimerExists(fallTimerHandle))
		GetWorld()->GetTimerManager().PauseTimer(fallTimerHandle);
	if (GetWorld()->GetTimerManager().TimerExists(movementCooldownTimerHandle))
		GetWorld()->GetTimerManager().PauseTimer(movementCooldownTimerHandle);

	playerCouldMoveBeforePause = playerCanMove;
	playerCanMove = false;

}

void ABoard::ResumeGame()
{
	if (!gameStarted || !gameIsPaused) return;
	gameIsPaused = false;

	if (GetWorld()->GetTimerManager().TimerExists(fallTimerHandle))
		GetWorld()->GetTimerManager().UnPauseTimer(fallTimerHandle);
	if (GetWorld()->GetTimerManager().TimerExists(movementCooldownTimerHandle))
		GetWorld()->GetTimerManager().UnPauseTimer(movementCooldownTimerHandle);

	playerCanMove = playerCouldMoveBeforePause;
}
