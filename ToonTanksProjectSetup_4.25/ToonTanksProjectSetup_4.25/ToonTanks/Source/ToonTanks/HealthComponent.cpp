// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = MaxHealth; // Initialize health to max health

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || Health <= 0.f)
	{
		return; // No damage or already dead
	}

	Health -= Damage;
	if (Health <= 0.f)
	{
		// Handle death logic here
		UE_LOG(LogTemp, Warning, TEXT("Actor %s has died."), *DamagedActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s took damage. Current health: %f"), *DamagedActor->GetName(), Health);
	}
}

