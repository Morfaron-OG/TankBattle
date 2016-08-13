// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// subscribe local method to tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this,
			&ATankAIController::OnTankDeath);
	}
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

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("DEAD"))
}