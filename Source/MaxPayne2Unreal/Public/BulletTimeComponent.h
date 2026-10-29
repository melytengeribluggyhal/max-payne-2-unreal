#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletTimeComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAXPAYNE2UNREAL_API UBulletTimeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBulletTimeComponent();

    void Activate(float TimeScale = 0.35f, float DurationSeconds = 4.0f);
    void Deactivate();
    bool IsActive() const;
    float GetTimeScale() const;

protected:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

private:
    bool bActive = false;
    float ActiveTimeScale = 1.0f;
    float RemainingSeconds = 0.0f;
};
