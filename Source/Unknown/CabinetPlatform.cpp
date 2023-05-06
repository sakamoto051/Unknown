// Fill out your copyright notice in the Description page of Project Settings.


#include "CabinetPlatform.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

// Sets default values
ACabinetPlatform::ACabinetPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACabinetPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACabinetPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACabinetPlatform::DestroyOwn()
{
	TArray<UAudioComponent*> AudioComponents;
	GetComponents<UAudioComponent>(AudioComponents);
	UAudioComponent* DestroyedComponent = nullptr;
	for (UAudioComponent* AudioComponent : AudioComponents) {
		if (AudioComponent->GetName() == TEXT("Destroyed")) {
			DestroyedComponent = AudioComponent;
			break;
		}
	}
	if (DestroyedComponent) {
		DestroyedComponent->Play();
		FVector Location = FVector(-1098.000000, -1057.000000, 20.000000);
		FRotator Rotation = FRotator(-90.000000, 172.874984, -12.874982);
		SetActorLocation(Location);
		SetActorRotation(Rotation);
	}
}

