// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->
		FindComponentByClass<UTankAimingComponent>();
	if(!ensure(AimingComponent))
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Player controller can't find tank aiming component"));
		return;
	}
	else
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()){ return; }

	FVector HitLocation = FVector(0); //OUT parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->
			AimAt(HitLocation);
	}
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
	const FName TraceTag("MyTraceTatg");

	//GetWorld()->DebugDrawTraceTag = TraceTag;

	FCollisionQueryParams CollisionParams;
	CollisionParams.TraceTag = TraceTag;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation,
		ECollisionChannel::ECC_Visibility, CollisionParams))
	{
		HitLocation = Hit.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
