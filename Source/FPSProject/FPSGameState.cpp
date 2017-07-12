#include "FPSGameState.h"
#include "Net/UnrealNetwork.h"

AFPSGameState::AFPSGameState()
{
	CurrentState = EGamePlayState::EUnknown;
}

void AFPSGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSGameState, CurrentState);
	DOREPLIFETIME(AFPSGameState, WinningPlayerName);
}

EGamePlayState AFPSGameState::GetCurrentState() const
{
	return CurrentState;
}

void AFPSGameState::SetCurrentState(EGamePlayState NewState)
{
	if (Role == ROLE_Authority) {
		CurrentState = NewState;
	}
}

void AFPSGameState::OnRep_CurrentState()
{

}





