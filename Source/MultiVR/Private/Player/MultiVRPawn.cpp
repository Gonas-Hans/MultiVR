// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Player/MultiVRPawn.h"

// Sets default values
AMultiVRPawn::AMultiVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize the player's Health
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

}

void AMultiVRPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	//Replicate current health.
	DOREPLIFETIME(AMultiVRPawn, CurrentHealth);
}

// Called when the game starts or when spawned
void AMultiVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMultiVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMultiVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMultiVRPawn::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

void AMultiVRPawn::OnHealthUpdate()
{
	//Client-specific functionality
	if (IsLocallyControlled())
	{
		FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

		if (CurrentHealth <= 0)
		{
			FString deathMessage = FString::Printf(TEXT("You have been killed."));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
		}
	}

	//Server-specific functionality
	if (GetLocalRole() == ROLE_Authority)
	{
		FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	}

	//Functions that occur on all machines. 
	/*  
		Any special functionality that should occur as a result of damage or death should be placed here. 
	*/
}

void AMultiVRPawn::SetCurrentHealth(float healthValue)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentHealth = FMath::Clamp(healthValue, 0.f, MaxHealth);
		OnHealthUpdate();
	}
}

float AMultiVRPawn::TakeDamage(float DamageTaken, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float damageApplied = CurrentHealth - DamageTaken;
	SetCurrentHealth(damageApplied);
	return damageApplied;
}

