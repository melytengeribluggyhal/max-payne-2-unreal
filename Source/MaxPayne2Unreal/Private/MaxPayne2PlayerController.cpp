#include "MaxPayne2PlayerController.h"
#include "MaxPayne2Character.h"
#include "Engine/World.h"

AMaxPayne2PlayerController::AMaxPayne2PlayerController()
{
    // Basic third-person camera defaults.
    // Adjust offsets once the actual Max Payne 2 camera rig is added.
}

void AMaxPayne2PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveForward", this, &AMaxPayne2PlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AMaxPayne2PlayerController::MoveRight);
    InputComponent->BindAxis("LookUp", this, &AMaxPayne2PlayerController::LookUp);
    InputComponent->BindAxis("Turn", this, &AMaxPayne2PlayerController::Turn);
    InputComponent->BindAction("Fire", IE_Pressed, this, &AMaxPayne2PlayerController::Fire);
}

void AMaxPayne2PlayerController::MoveForward(float Value)
{
    if (Value != 0.0f && GetPawn())
    {
        GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), Value);
    }
}

void AMaxPayne2PlayerController::MoveRight(float Value)
{
    if (Value != 0.0f && GetPawn())
    {
        GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), Value);
    }
}

void AMaxPayne2PlayerController::LookUp(float Value)
{
    if (Value != 0.0f)
    {
        AddControllerPitchInput(Value);
    }
}

void AMaxPayne2PlayerController::Turn(float Value)
{
    if (Value != 0.0f)
    {
        AddControllerYawInput(Value);
    }
}

void AMaxPayne2PlayerController::Fire()
{
    if (!GetPawn())
    {
        return;
    }

    if (AMaxPayne2Character* Character = Cast<AMaxPayne2Character>(GetPawn()))
    {
        Character->BeginBulletTime(0.55f, 1.2f);
    }

    UE_LOG(LogTemp, Log, TEXT("Fire action triggered (skeleton)."));
}
