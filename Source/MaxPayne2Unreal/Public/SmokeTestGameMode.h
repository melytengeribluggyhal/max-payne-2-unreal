#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SmokeTestGameMode.generated.h"

UCLASS()
class MAXPAYNE2UNREAL_API ASmokeTestGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASmokeTestGameMode();
    virtual void StartPlay() override;
};
