// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameState.h"
#include "FPSProjectGameModeBase.generated.h"

/**
*
*/
UCLASS()
class FPSPROJECT_API AFPSProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSProjectGameModeBase();

	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite)
		FString LastKiller;
	UPROPERTY(BlueprintReadWrite)
		FString LastVictim;
	UPROPERTY(BlueprintReadWrite)
		bool AddKillFeedEntry;
	UFUNCTION(BlueprintImplementableEvent)
		void ActuallyAddKillFeedEntry();

protected:
	//how many times per second to update the game's UI and State
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		float UpdateDelay;

	FTimerHandle UpdateTimer;
private:

	void Update();
	//handfle function calls for when the game transitions between states
	void HandleNewState(EGamePlayState NewState);



};

