// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackSet,
	UTankTrack* RightTrackSet)
{
	LeftTrack = LeftTrackSet;
	RightTrack = RightTrackSet;
}

void UTankMovementComponent::IntendMoveForwards(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	Throw = FMath::Clamp<float>(Throw, 0, 1);
	//UE_LOG(LogTemp, Warning, TEXT("Intend move fwd: %f"),  Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveBackwards(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	Throw = FMath::Clamp<float>(Throw, -1, 0);
	//UE_LOG(LogTemp, Warning, TEXT("Intend move Bwd: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	Throw = FMath::Clamp<float>(Throw, 0, 1);
	//UE_LOG(LogTemp, Warning, TEXT("Intend clock: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IntendRotateCClockwise(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	Throw = FMath::Clamp<float>(Throw, -1, 0);
	//UE_LOG(LogTemp, Warning, TEXT("Intend cclock: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}