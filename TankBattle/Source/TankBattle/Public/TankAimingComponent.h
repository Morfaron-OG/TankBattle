// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
//Forward Declaration
class UTankBarrel;

//Controls Barrel and Turret Aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void AimAt(FVector HitLocation, float LaunchSpeedParam);

private:
	UTankBarrel* Barrel = nullptr;
	
	void MoveBarrelTowards(FVector AimDirection);
};
