// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction *TickThisFunction)
{

}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
	const FHitResult& Hit)
{
	ApplySidewaysForce();
	DriveTrack();
	CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(),
		GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime)*GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->
		GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * 
		TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

