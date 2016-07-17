// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetPawn();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s possesing %s."),
			*GetName(),
			*ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No tank possesed by player!"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("ticking!"));

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




