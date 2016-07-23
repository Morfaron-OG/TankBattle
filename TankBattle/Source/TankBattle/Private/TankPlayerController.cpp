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
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()){ return; }

	FVector HitLocation = FVector(0); //OUT parameter
	GetSightRayHitLocation(HitLocation);
	UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector LookDirection;
	FVector2D ScreenLocation = FVector2D(CrosshairXLocation * ViewportSizeX,
		CrosshairYLocation * ViewportSizeY);

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation,
		FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
		CameraWorldLocation, LookDirection));
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDir,
		FVector& HitLocation) const
{
	FHitResult Hit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDir * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = Hit.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
