// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorPlatform.h"
#include "Kismet/GameplayStatics.h"
#include "CabinetPlatform.h"

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

void ADoorPlatform::PlayKnockSound()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Door"), FoundActors);
	for (AActor* Actor : FoundActors) {
		FString ActorName = Actor->GetName();
		if (ActorName == "BP_Door2_C_2") {
			Cast<ADoorPlatform>(Actor)->IsKnocking = true;
		}
	}
}

void ADoorPlatform::StopKnockSound()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Door"), FoundActors);
	for (AActor* Actor : FoundActors) {
		FString ActorName = Actor->GetName();
		if (ActorName == "BP_Door2_C_2") {
			Cast<ADoorPlatform>(Actor)->IsKnocking = false;
		}
	}
}

void ADoorPlatform::DestroyCabinet()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Cabinet"), FoundActors);
	for (AActor* Actor : FoundActors) {
		FString ActorName = Actor->GetName();
		if (ActorName == "BP_CabinetPlatform_C_3") {
			Cast<ACabinetPlatform>(Actor)->DestroyOwn();
		}
	}
}

void ADoorPlatform::StopAll()
{
	UE_LOG(LogTemp, Display, TEXT("Stop All!!!!!"));
}
