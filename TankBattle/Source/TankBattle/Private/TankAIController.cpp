// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s possesing %s."),
			*GetName(),
			*ControlledTank->GetName());
		if (GetPlayerTank())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s found player %s."),
				*GetName(),
				*GetPlayerTank()->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No player tank found!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No tank possesed by AI!"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) 
	{
		AimTowardsPlayer();
	}
	
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank)
	{
		return Cast<ATank>(PlayerTank);
	}
	return nullptr;
}

void ATankAIController::AimTowardsPlayer()
{
	if (!GetControlledTank()) { return; }
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

