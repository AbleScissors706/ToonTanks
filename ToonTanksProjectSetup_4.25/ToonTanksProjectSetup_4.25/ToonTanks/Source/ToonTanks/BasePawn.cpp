// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	if (TurretMesh)
	{
		FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
		FRotator TurretRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
		TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), TurretRotation, GetWorld()->GetDeltaSeconds(), 5.f));
	}
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	 // Calculate the forward vector of the spawn point
    FVector ForwardVector = ProjectileSpawnPoint->GetForwardVector();

    // Define the desired offset distance (e.g., 100 units)
    float OffsetDistance = 100.f;

    // Calculate the new spawn location by adding the offset in the forward direction
    FVector OffsetLocation = Location + ForwardVector * OffsetDistance;

    // Spawn the projectile at the offset location
    GetWorld()->SpawnActor<AProjectile>(ProjectileClass, OffsetLocation, Rotation);

}
