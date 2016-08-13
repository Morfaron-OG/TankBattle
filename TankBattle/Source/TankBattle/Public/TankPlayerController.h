// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Player control tank
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	virtual void SetPawn(APawn* InPawn) override;
	
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

	UFUNCTION()
		void OnTankDeath();
};