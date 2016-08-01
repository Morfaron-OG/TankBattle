// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	/*Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	UE_LOG(LogTemp, Warning, TEXT("%s throttle value: %f"),
		*GetName(), Throttle);*/

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); 
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

