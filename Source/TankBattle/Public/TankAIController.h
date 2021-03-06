// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * Controller for AI Tanks
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	virtual void SetPawn(APawn* InPawn) override;

	// How close AI can get to player.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 5000;

	UFUNCTION()
		void OnTankDeath();
};
