#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MaxPayne2PlayerController.generated.h"

UCLASS()
class MAXPAYNE2UNREAL_API AMaxPayne2PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMaxPayne2PlayerController();

    virtual void SetupInputComponent() override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookUp(float Value);
    void Turn(float Value);
    void Fire();
};
