// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorPlatform.h"

// Sets default values
ADoorPlatform::ADoorPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorPlatform::Interact()
{
	OnInteract();
}

