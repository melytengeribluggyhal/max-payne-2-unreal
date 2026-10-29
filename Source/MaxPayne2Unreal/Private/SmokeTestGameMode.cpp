#include "SmokeTestGameMode.h"
#include "StickFigurePawn.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"

static UStaticMesh* LoadBasicMesh(const TCHAR* Path)
{
    return LoadObject<UStaticMesh>(nullptr, Path);
}

ASmokeTestGameMode::ASmokeTestGameMode()
{
    DefaultPawnClass = AStickFigurePawn::StaticClass();
}

void ASmokeTestGameMode::StartPlay()
{
    Super::StartPlay();

    if (UWorld* World = GetWorld())
    {
        UStaticMesh* Cube = LoadBasicMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
        if (!Cube)
        {
            UE_LOG(LogTemp, Warning, TEXT("SmokeTest: basic cube mesh not found."));
            return;
        }

        auto SpawnBlock = [&](const FVector& Location, const FVector& Scale)
        {
            AStaticMeshActor* Actor = World->SpawnActor<AStaticMeshActor>(
                AStaticMeshActor::StaticClass(), Location, FRotator::ZeroRotator);
            if (Actor && Actor->GetStaticMeshComponent())
            {
                Actor->GetStaticMeshComponent()->SetStaticMesh(Cube);
                Actor->GetStaticMeshComponent()->SetRelativeScale3D(Scale);
                Actor->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            }
        };

        // Small procedural scene: floor and two low blocks. No assets or textures.
        SpawnBlock(FVector(0.0f, 0.0f, 0.0f), FVector(8.0f, 8.0f, 0.2f));
        SpawnBlock(FVector(-2.6f, -1.8f, 0.35f), FVector(0.8f, 0.8f, 0.7f));
        SpawnBlock(FVector(2.6f, 1.4f, 0.25f), FVector(0.6f, 0.6f, 0.5f));

        UE_LOG(LogTemp, Log, TEXT("SmokeTest scene spawned."));
    }
}
