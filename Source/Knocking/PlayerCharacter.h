// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KnockingCharacter.h"
#include "Sound/SoundCue.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KNOCKING_API APlayerCharacter : public AKnockingCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	UAudioComponent* FootstepAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundCue* FootstepSoundCue;
	
public:
	APlayerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact();
	void ToggleCrouched();
	UFUNCTION(BlueprintCallable)
	void ClearInputBind();
	UFUNCTION(BlueprintCallable)
	void SetInputBind();
	UFUNCTION(BlueprintCallable)
	void SetMenuInputBind();
	UFUNCTION(BlueprintCallable)
	void ActivateCursor();
	UFUNCTION(BlueprintCallable)
	void DeActivateCursor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanMove = true;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void SoundFootStep();
	void ToggleMenu();

	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	
	float MaxRange = 100;

	UPROPERTY(VisibleAnywhere)
	bool IsCrouched;
	UPROPERTY(VisibleAnywhere)
	bool IsOpenMenu = false;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> TitleWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ClearWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MenuWidget;

	UFUNCTION(BlueprintCallable)
	void SetTitleWidget();
	UFUNCTION(BlueprintCallable)
	void SetClearWidget();
	UFUNCTION(BlueprintCallable)
	void SetMenuWidget();
	UFUNCTION(BlueprintCallable)
	void RemoveMenuWidget();
};
