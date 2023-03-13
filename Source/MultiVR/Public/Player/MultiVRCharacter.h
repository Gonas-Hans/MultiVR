// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MultiVRCharacter.generated.h"

UCLASS()
class MULTIVR_API AMultiVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMultiVRCharacter();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Health
	protected:
	// The player's maximum health
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	// The player's current health
	UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth)
	float CurrentHealth;

	//RepNotify for changes made to current health
	UFUNCTION()
	void OnRep_CurrentHealth();

	// Response to health being updated
	void OnHealthUpdate();

	//Damage
	public:
	/** Getter for Max Health.*/
	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; } 

	/** Getter for Current Health.*/
	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	/** Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. Should only be called on the server.*/
	UFUNCTION(BlueprintCallable, Category="Health")
	void SetCurrentHealth(float healthValue);

	/** Event for taking damage. Overridden from APawn.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	float TakeDamage( float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser ) override;

	//Fire

	/** Function for beginning weapon fire.*/
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void Fire(FVector Start, FVector End);

};
