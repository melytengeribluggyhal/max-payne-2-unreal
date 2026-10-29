#include "StickFigurePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/StaticMesh.h"

static UStaticMesh* LoadBasicMesh(const TCHAR* Path)
{
    return LoadObject<UStaticMesh>(nullptr, Path);
}

AStickFigurePawn::AStickFigurePawn()
{
    UCapsuleComponent* Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
    Capsule->InitCapsuleSize(0.35f, 1.0f);
    Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    RootComponent = Capsule;

    UStaticMesh* Cylinder = LoadBasicMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    UStaticMesh* Sphere = LoadBasicMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

    Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    Body->SetupAttachment(RootComponent);
    Body->SetStaticMesh(Cylinder);
    Body->SetRelativeLocation(FVector(0.0f, 0.0f, 0.95f));
    Body->SetRelativeScale3D(FVector(0.12f, 0.12f, 0.9f));

    Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
    Head->SetupAttachment(RootComponent);
    Head->SetStaticMesh(Sphere);
    Head->SetRelativeLocation(FVector(0.0f, 0.0f, 1.55f));
    Head->SetRelativeScale3D(FVector(0.18f, 0.18f, 0.18f));

    LeftArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftArm"));
    LeftArm->SetupAttachment(RootComponent);
    LeftArm->SetStaticMesh(Cylinder);
    LeftArm->SetRelativeLocation(FVector(-0.42f, 0.0f, 1.15f));
    LeftArm->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
    LeftArm->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.48f));

    RightArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightArm"));
    RightArm->SetupAttachment(RootComponent);
    RightArm->SetStaticMesh(Cylinder);
    RightArm->SetRelativeLocation(FVector(0.42f, 0.0f, 1.15f));
    RightArm->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
    RightArm->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.48f));

    LeftLeg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLeg"));
    LeftLeg->SetupAttachment(RootComponent);
    LeftLeg->SetStaticMesh(Cylinder);
    LeftLeg->SetRelativeLocation(FVector(-0.16f, 0.0f, 0.35f));
    LeftLeg->SetRelativeScale3D(FVector(0.06f, 0.06f, 0.7f));

    RightLeg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightLeg"));
    RightLeg->SetupAttachment(RootComponent);
    RightLeg->SetStaticMesh(Cylinder);
    RightLeg->SetRelativeLocation(FVector(0.16f, 0.0f, 0.35f));
    RightLeg->SetRelativeScale3D(FVector(0.06f, 0.06f, 0.7f));

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 1.25f));
    SpringArm->TargetArmLength = 4.5f;
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void AStickFigurePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Turn", this, &AStickFigurePawn::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AStickFigurePawn::LookUp);
    PlayerInputComponent->BindAxis("MoveForward", this, &AStickFigurePawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AStickFigurePawn::MoveRight);
}

void AStickFigurePawn::Turn(float Value)
{
    if (Value != 0.0f)
    {
        AddControllerYawInput(Value);
    }
}

void AStickFigurePawn::LookUp(float Value)
{
    if (Value != 0.0f)
    {
        AddControllerPitchInput(Value);
    }
}

void AStickFigurePawn::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void AStickFigurePawn::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}
