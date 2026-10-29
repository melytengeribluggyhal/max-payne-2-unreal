#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MaxPayne2Character.generated.h"

class UBulletTimeComponent;

UCLASS()
class MAXPAYNE2UNREAL_API AMaxPayne2Character : public ACharacter
{
    GENERATED_BODY()

public:
    AMaxPayne2Character();

    void BeginBulletTime(float TimeScale = 0.35f, float DurationSeconds = 4.0f);
    void EndBulletTime();
    bool IsBulletTimeActive() const;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Time")
    UBulletTimeComponent* BulletTime;
};
