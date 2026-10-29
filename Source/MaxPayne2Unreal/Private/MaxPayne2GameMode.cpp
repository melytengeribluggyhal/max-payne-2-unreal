#include "MaxPayne2GameMode.h"
#include "MaxPayne2Character.h"
#include "MaxPayne2PlayerController.h"

AMaxPayne2GameMode::AMaxPayne2GameMode()
{
    DefaultPawnClass = AMaxPayne2Character::StaticClass();
    PlayerControllerClass = AMaxPayne2PlayerController::StaticClass();
}

void AMaxPayne2GameMode::StartPlay()
{
    Super::StartPlay();
    UE_LOG(LogTemp, Log, TEXT("MaxPayne2Unreal game mode started."));
}
