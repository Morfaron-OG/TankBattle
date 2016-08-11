// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = GetPawn();
	auto PlayerControlledTank = 
		GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ControlledTank) { return; }
	if (PlayerControlledTank)
	{
		//Move towards player
		MoveToActor(PlayerControlledTank, AcceptanceRadius);

		// Aim at player
		ControlledTank->FindComponentByClass<UTankAimingComponent>()->
			AimAt(PlayerControlledTank->GetActorLocation() + 
				FVector(0, 0, 150));

		if (ControlledTank->FindComponentByClass<UTankAimingComponent>()->
			GetFiringStatus() == EFiringStatus::Locked)
		{
			ControlledTank->FindComponentByClass<UTankAimingComponent>()->
				FireProjectile();
		}
	}	
}
