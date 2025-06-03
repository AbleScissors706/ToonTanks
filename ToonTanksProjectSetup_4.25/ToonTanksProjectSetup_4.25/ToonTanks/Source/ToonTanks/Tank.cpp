// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    // Set this pawn to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    SpringArm->SetupAttachment(RootComponent);
    Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind movement input
    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
    PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FHitResult HitResult;

    if(PlayerControllerRef)
    {
        PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
        
    }
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));

}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value * Speed * GetWorld()->GetDeltaSeconds();
    AddActorLocalOffset(DeltaLocation);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * TurnRate * GetWorld()->GetDeltaSeconds();
    AddActorLocalRotation(DeltaRotation, true);
}