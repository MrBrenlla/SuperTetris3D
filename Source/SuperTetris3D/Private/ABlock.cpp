// Fill out your copyright notice in the Description page of Project Settings.


#include "ABlock.h"
#include "ABoard.h"
#include "AFloatingScore.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = false;

	blockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	RootComponent = blockMesh;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Script/Engine.StaticMesh'/Game/Models/Block.Block'"));
	blockMesh->SetStaticMesh(MeshObj.Object);


	isMoving = true;
	isGolden = false;

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{

	if (DefaultMesh)
	{
		blockMesh->SetStaticMesh(DefaultMesh);
	}

	Super::BeginPlay();
	
}


void ABlock::MakeStatic()
{
	movable = false;
	isMoving = false;
}

void ABlock::SetXY(int32 newX, int32 newY)
{
	x = newX;
	y = newY;

	SetActorLocation(FVector(0.f, x * -100.f, y* 100.f));
}

bool ABlock::MustMove()
{
	if (!movable) return false;
	isMoving = true;
	return true;
}

int ABlock::BreackBlock(int mult)
{
	if (!movable) return -1;

	for(ABlock* b : conectedBlocks)
	{
		b->conectedBlocks.Remove(this);
	}
	conectedBlocks.Empty();
	
	Destroy();

	return ShowScore(mult);
}

void ABlock::ConectBlock(ABlock* block)
{
	if (!movable || !block->movable) return;
	conectedBlocks.Add(block);
	block->conectedBlocks.Add(this);
}

void ABlock::SetMaterial(UMaterialInterface* mat)
{
	blockMesh->SetMaterial(0, mat);
}

void ABlock::SetGolden()
{
	isGolden = true;
}

//Only use if all blocs are going to be removed, to avoid errors with conected blocks
bool ABlock::SilentDestroy()
{
	if (movable) {
		return Destroy();
	}
	return false;
}

void ABlock::StopMovement(ABoard* board)
{
	if (!movable) return;

	if (!isMoving) return;

	isMoving = false;

	board->FixBlock(this);

	for (ABlock* b : conectedBlocks)
	{
		if(b->isMoving==true) b->StopMovement(board);
	}
	
}

int ABlock::ShowScore(int mult)
{
	FVector SpawnPos = GetActorLocation() + FVector(0, 0, 0);

	int score;

	if(isGolden) score = 50 * mult;
	else score = 10 * mult;

	if (UWorld* World = GetWorld())
	{
		
		AFloatingScore* ScoreActor = World->SpawnActor<AFloatingScore>(
			AFloatingScore::StaticClass(),
			SpawnPos,
			FRotator::ZeroRotator
		);

		if (ScoreActor)
		{
			if(isGolden) ScoreActor->SetColor(FColor::Yellow);

			ScoreActor->SetScore(score);
		}

	}

	return score;
}

