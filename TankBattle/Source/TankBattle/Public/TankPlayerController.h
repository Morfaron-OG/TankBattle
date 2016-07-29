// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	
	void AimTowardsCrosshair(); //Move tank barrel so shot intersects crosshair

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, 
		FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation,
			FVector& LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;
};