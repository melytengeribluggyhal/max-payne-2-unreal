#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MaxPayne2GameMode.generated.h"

UCLASS()
class MAXPAYNE2UNREAL_API AMaxPayne2GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMaxPayne2GameMode();

    // Optional hook for future bullet-time-aware game rules.
    virtual void StartPlay() override;
};
