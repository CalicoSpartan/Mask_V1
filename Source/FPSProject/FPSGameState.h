#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

UENUM(BlueprintType)
enum EGamePlayState
{
	EWaiting,
	EPlaying,
	EGameOver,
	EUnknown
};


/**
*
*/
UCLASS()
class FPSPROJECT_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AFPSGameState();

	//required network scaffolding
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//this returns the current state of gameplay
	UFUNCTION(BlueprintPure)
		EGamePlayState GetCurrentState() const;
	//transition game into a new play state, Only usable on server
	void SetCurrentState(EGamePlayState NewState);

	// rep notify fired on clients to allow for client side changes in gameplay state
	UFUNCTION()
		void OnRep_CurrentState();

	// name of player who won the game
	UPROPERTY(Replicated, BlueprintReadWrite)
		FString WinningPlayerName;
private:
	// track the current playing state
	UPROPERTY(ReplicatedUsing = OnRep_CurrentState)
		TEnumAsByte<enum EGamePlayState> CurrentState;


};

