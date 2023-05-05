// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPlatform.generated.h"

UCLASS()
class UNKNOWN_API ALightPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFlashing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsTurnedOn;

	UFUNCTION()
	void Interact();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();
};
