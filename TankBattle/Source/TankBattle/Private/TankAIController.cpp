// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetPawn()) { return; }
	if (GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		//Move towards player
		MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(),
			AcceptanceRadius);

		// Aim at player
		Cast<ATank>(GetPawn())->
			AimAt(GetWorld()->GetFirstPlayerController()->GetPawn()->
				GetActorLocation()+FVector(0,0,100));

		Cast<ATank>(GetPawn())->FireProjectile();
	}	
}
