#include "BulletTimeComponent.h"
#include "Engine/World.h"
#include "GameFramework/WorldSettings.h"

UBulletTimeComponent::UBulletTimeComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UBulletTimeComponent::Activate(float TimeScale, float DurationSeconds)
{
    if (TimeScale <= 0.0f || DurationSeconds <= 0.0f)
    {
        return;
    }

    bActive = true;
    ActiveTimeScale = TimeScale;
    RemainingSeconds = DurationSeconds;

    if (UWorld* World = GetWorld())
    {
        World->GetWorldSettings()->SetTimeDilation(ActiveTimeScale);
    }
}

void UBulletTimeComponent::Deactivate()
{
    bActive = false;
    RemainingSeconds = 0.0f;
    ActiveTimeScale = 1.0f;

    if (UWorld* World = GetWorld())
    {
        World->GetWorldSettings()->SetTimeDilation(1.0f);
    }
}

bool UBulletTimeComponent::IsActive() const
{
    return bActive;
}

float UBulletTimeComponent::GetTimeScale() const
{
    return ActiveTimeScale;
}

void UBulletTimeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bActive)
    {
        return;
    }

    RemainingSeconds -= DeltaTime;
    if (RemainingSeconds <= 0.0f)
    {
        Deactivate();
    }
}
