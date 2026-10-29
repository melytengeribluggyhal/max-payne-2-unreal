#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StickFigurePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;

UCLASS()
class MAXPAYNE2UNREAL_API AStickFigurePawn : public APawn
{
    GENERATED_BODY()

public:
    AStickFigurePawn();

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Body;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Head;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* LeftArm;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* RightArm;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* LeftLeg;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* RightLeg;
};
