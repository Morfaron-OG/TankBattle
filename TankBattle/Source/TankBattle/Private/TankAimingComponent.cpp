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
	/*auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName,
		*HitLocation.ToString(), *BarrelLocation.ToString());*/

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,
		OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	//auto Time = GetWorld()->GetTimeSeconds();
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found!"),
		//	Time);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found!"),
		//	Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotator - BarrelRotator;
	float TurretRelSpeed = 0;
	if (FMath::Abs<float>(DeltaRotator.Yaw) > 0.05)
	{
		if (DeltaRotator.Yaw >= 180 ||
			(DeltaRotator.Yaw < 0 && DeltaRotator.Yaw >= -180))
		{
			TurretRelSpeed = -FMath::Abs<float>(DeltaRotator.Yaw);
		}
		else
		{
			TurretRelSpeed = FMath::Abs<float>(DeltaRotator.Yaw);
		}
	}
	/*UE_LOG(LogTemp, Warning, TEXT("\nAR: %s"),
		*AimAtRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("BR: %s"),
		*BarrelRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("DR: %s"),
		*DeltaRotator.ToString());*/
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->TurretRotate(TurretRelSpeed);
}

void UTankAimingComponent::FireProjectile()
{
	bool bIsReloaded =
		(FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("Firing!"));
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