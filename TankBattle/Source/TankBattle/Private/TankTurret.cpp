// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTurret.h"

void UTankTurret::TurretRotate(float RelativeSpeed)
{
	auto RelativeSpeedClamp = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeedClamp * MaxDegreesPerSecond *
		GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
	//UE_LOG(LogTemp, Warning, TEXT("%f: Turret rotation"),
	//	RawNewRotation);
}


