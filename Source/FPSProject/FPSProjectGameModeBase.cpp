// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProjectGameModeBase.h"
#include "FPSCharacter.h"
#include "PlayerHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

AFPSProjectGameModeBase::AFPSProjectGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_FPSCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	// set the type of HUD used in the game
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Blueprints/BP_PlayerHUD"));
	if (PlayerHUDClass.Class != NULL) {
		HUDClass = PlayerHUDClass.Class;
	}
	

	AddKillFeedEntry = false;
	//set the type of gamestate used in the game
	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	check(World);
	AFPSGameState* MyGameState = Cast<AFPSGameState>(GameState);
	check(MyGameState);
	HandleNewState(EGamePlayState::EPlaying);


}

void AFPSProjectGameModeBase::Update()
{
	UWorld* World = GetWorld();
	check(World);
	AFPSGameState* MyGameState = Cast<AFPSGameState>(GameState);
	check(MyGameState);

	for (FConstControllerIterator It = World->GetControllerIterator(); It; ++It) {
		if (APlayerController* PlayerController = Cast<APlayerController>(*It)) {
			if (AFPSCharacter* Player = Cast<AFPSCharacter>(PlayerController->GetPawn())) {
				if (Player->GetCurrentHealth() <= 0.0f) {
					if (Player->Shooter == NULL) {
						Player->Shooter = Player;
					}
					UE_LOG(LogClass, Log, TEXT("KILLED"));
					//if (APlayerHUD* TheHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())) {
					LastKiller = Player->Shooter->GetName();
					LastVictim = Player->GetName();
					AddKillFeedEntry = true;
					Player->OnPlayerDeath();
						//TheHUD->AddMessageEvent();
						//ActuallyAddKillFeedEntry();
					
					//}





				}
			}
		}
	}
}

void AFPSProjectGameModeBase::HandleNewState(EGamePlayState NewState)
{
	UWorld* World = GetWorld();
	check(World);
	AFPSGameState* MyGameState = Cast<AFPSGameState>(GameState);
	check(MyGameState);

	if (NewState != MyGameState->GetCurrentState())
	{
		//update the state, so clients know about the transition
		MyGameState->SetCurrentState(NewState);

		switch (NewState)
		{
		case EGamePlayState::EWaiting:

			break;
		case EGamePlayState::EPlaying:

			//start draining power
			GetWorldTimerManager().SetTimer(UpdateTimer, this, &AFPSProjectGameModeBase::Update, UpdateDelay, true);
			break;
		case EGamePlayState::EGameOver:

			//stop draining power
			GetWorldTimerManager().ClearTimer(UpdateTimer);
			break;
		default:
		case EGamePlayState::EUnknown:
			break;
		}
	}

}



