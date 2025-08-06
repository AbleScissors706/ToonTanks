// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    // Handle the logic when an actor dies
    if (DeadActor == Tank)
    {
       Tank->HandleDestruction();
       if(Tank->GetTankPlayerController())
       {
           Tank->DisableInput(Tank->GetTankPlayerController());
           Tank->GetTankPlayerController()->bShowMouseCursor = false;
       }
       
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
    }
 
    
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Initialize the Tank reference
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (Tank)
    {
        // You can set up additional logic for the tank here if needed
        UE_LOG(LogTemp, Warning, TEXT("Tank initialized: %s"), *Tank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize Tank!"));
    }
}