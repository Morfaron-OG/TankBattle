// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	
	void AimTowardsCrosshair(); //Move tank barrel so shot intersects crosshair

private:
	bool GetSightRayHitLocation(FVector& HitLocation) const;
};
