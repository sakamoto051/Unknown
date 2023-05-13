// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPlatform.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

// Sets default values
APaintingPlatform::APaintingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APaintingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaintingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APaintingPlatform::Interact()
{
	OnInteract();

	if (!IsBlood) {
		APaintingPlatform::DelayFunction(2);
	}
}

void APaintingPlatform::DelayFunction(float DelayTime)
{
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APaintingPlatform::DelayedFunctionCall, DelayTime, false);
}

void APaintingPlatform::DelayedFunctionCall()
{
	TArray<UMeshComponent*> MeshComponents;
    GetComponents<UMeshComponent>(MeshComponents);
    for (auto MeshComp : MeshComponents) {
        MeshComp->SetMaterial(0, ChangedMaterial);
    }
	APaintingPlatform::IsBlood = true;

	TArray<UAudioComponent*> AudioComponents;
	GetComponents<UAudioComponent>(AudioComponents);
	UAudioComponent* BloodSound = nullptr;
	for (UAudioComponent* AudioComponent : AudioComponents) {
		if (AudioComponent->GetName() == TEXT("BloodSound")) {
			BloodSound = AudioComponent;
			break;
		}
	}
	if (BloodSound) {
		BloodSound->Play();
	}
}