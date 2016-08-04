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

	// How close AI can get to player.
	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 7000;
};
