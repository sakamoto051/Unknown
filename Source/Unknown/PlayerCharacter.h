// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnknownCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNKNOWN_API APlayerCharacter : public AUnknownCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact();
	void ToggleCrouched();

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	
	float MaxRange = 100;

	UPROPERTY(VisibleAnywhere)
	bool IsCrouched;
};
