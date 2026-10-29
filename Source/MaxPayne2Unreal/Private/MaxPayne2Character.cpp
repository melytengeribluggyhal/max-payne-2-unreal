#include "MaxPayne2Character.h"
#include "BulletTimeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMaxPayne2Character::AMaxPayne2Character()
{
    GetCharacterMovement()->MaxWalkSpeed = 400.0f;
    GetCharacterMovement()->JumpZVelocity = 400.0f;

    BulletTime = CreateDefaultSubobject<UBulletTimeComponent>(TEXT("BulletTime"));
    BulletTime->Activate(0.35f, 4.0f); // skeleton default, replace with input-driven activation
}

void AMaxPayne2Character::BeginBulletTime(float TimeScale, float DurationSeconds)
{
    if (BulletTime)
    {
        BulletTime->Activate(TimeScale, DurationSeconds);
    }
}

void AMaxPayne2Character::EndBulletTime()
{
    if (BulletTime)
    {
        BulletTime->Deactivate();
    }
}

bool AMaxPayne2Character::IsBulletTimeActive() const
{
    return BulletTime && BulletTime->IsActive();
}
