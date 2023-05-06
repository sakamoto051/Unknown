// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GamePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UNKNOWN_API AGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CheckedLockedDoor = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CheckedFrontDoor = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CheckedLivingLamp = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CheckedLockedDoorLamp = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CheckedLockedSecondFloorDoor = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Level2Flg = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LivingPainting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Level3Flg = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Level3NoisyFlg = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Level4Flg = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AllStopFlg = false;

    UFUNCTION(BlueprintImplementableEvent, Category="GamePlayerState")
    void SetFlg(const FString& ObjectName);

};
