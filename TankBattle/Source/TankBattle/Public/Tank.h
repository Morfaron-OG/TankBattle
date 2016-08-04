// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
protected:
private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(
		class UInputComponent* InputComponent) override;

};
