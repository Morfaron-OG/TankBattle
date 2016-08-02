// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Driving Tank Tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankTrack* LeftTrackSet, UTankTrack* RightTrackSet);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void IntendMoveForwards(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = Movement)
		void IntendMoveBackwards(float Throw);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void IntendRotateClockwise(float Throw);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void IntendRotateCClockwise(float Throw);
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
