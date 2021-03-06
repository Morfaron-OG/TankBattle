// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto RelativeSpeedClamp = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeedClamp * MaxDegreesPerSecond *
		GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation,
			MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel Elevation"),
	//	RawNewElevation);
}
