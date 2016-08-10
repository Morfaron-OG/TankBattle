// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction *TickThisFunction)
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(),
		GetComponentVelocity());
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime)*GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->
		GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

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

