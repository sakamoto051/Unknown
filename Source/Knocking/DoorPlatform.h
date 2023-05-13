// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorPlatform.generated.h"

UCLASS()
class KNOCKING_API ADoorPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanOpen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOpen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsKnocking;

	UFUNCTION()
	void Interact();
	UFUNCTION(BlueprintCallable)
	void PlayKnockSound();
	UFUNCTION(BlueprintCallable)
	void StopKnockSound();
	UFUNCTION(BlueprintCallable)
	void DestroyCabinet();
	UFUNCTION(BlueprintCallable)
	void StopAll();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();
};
