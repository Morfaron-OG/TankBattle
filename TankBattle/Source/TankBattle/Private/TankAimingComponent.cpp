// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


void UTankAimingComponent::Initialise(UTankTurret* TurretToSet,
	UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
		OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotator - BarrelRotator;
	float TurretRelSpeed = 0;
	bIsReloaded =
		(FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (FMath::Abs<float>(DeltaRotator.Yaw) > 0.05f || 
		FMath::Abs<float>(DeltaRotator.Pitch) > 0.05f)
	{
		if (bIsReloaded)
		{
			TankFiringStatus = EFiringStatus::Aiming;
		}
		else
		{
			TankFiringStatus = EFiringStatus::Reloading;
		}
		if (DeltaRotator.Yaw >= 180 ||
			(DeltaRotator.Yaw < 0 && DeltaRotator.Yaw >= -180))
		{
			TurretRelSpeed = -FMath::Abs<float>(DeltaRotator.Yaw);
		}
		else
		{
			TurretRelSpeed = FMath::Abs<float>(DeltaRotator.Yaw);
		}
		Turret->TurretRotate(TurretRelSpeed);
		Barrel->Elevate(DeltaRotator.Pitch);
	}
	else
	{
		if (bIsReloaded)
		{
			TankFiringStatus = EFiringStatus::Locked;
		}
		else
		{
			TankFiringStatus = EFiringStatus::Reloading;
		}
	}
}

void UTankAimingComponent::FireProjectile()
{
	if (Barrel && bIsReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}