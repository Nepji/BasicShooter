// Fill out your copyright notice in the Description page of Project Settings.


#include "BSGameModeBase.h"

#include "AIController.h"
#include "BSBaseCharacter.h"
#include "BSCoreUtils.h"
#include "BSPlayerController.h"
#include "BSPlayerState.h"
#include "EngineUtils.h"
#include "Components/BSRespawnComponent.h"
#include "Player/BSPlayerCharacter.h"

#include "UI/BSGameHUD.h"

ABSGameModeBase::ABSGameModeBase()
{
	DefaultPawnClass = ABSPlayerCharacter::StaticClass();
	PlayerControllerClass = ABSPlayerController::StaticClass();
	HUDClass = ABSGameHUD::StaticClass();
	PlayerStateClass = ABSPlayerState::StaticClass();
}
void ABSGameModeBase::Killed(AController* KillerController, AController* VictimController, const AController* AssistantController)
{
	const auto KillerPlayerState = KillerController ? Cast<ABSPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<ABSPlayerState>(VictimController->PlayerState) : nullptr;
	const auto AssistantPlayerState = AssistantController ? Cast<ABSPlayerState>(AssistantController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
	if (AssistantPlayerState)
	{
		AssistantPlayerState->AddAssist();
	}
	StartRespawn(VictimController);
}
bool ABSGameModeBase::CanRespawn() const
{
	return GameData.RespawnRate < RoundCountDown;
}
int32 ABSGameModeBase::GetRoundCountDown() const
{
	return RoundCountDown;
}
int32 ABSGameModeBase::GetCurrentMatchRound() const
{
	return CurrentRound;
}
int32 ABSGameModeBase::GetMatchRoundsCount() const
{
	return GameData.RoundNum;
}
void ABSGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
	
}
void ABSGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GameData.BotsEnabled)
	{
		SpawnBots();
	}
	CreateTeamInfo();
	CurrentRound = 1;
	StartRound();
}
UClass* ABSGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
void ABSGameModeBase::StartRound()
{
	RoundCountDown =  GameData.RoundTime;
	ResetPlayers();
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle,this,&ABSGameModeBase::GameTimerUpdate, 1.0f, true);
	UE_LOG(LogGameMode, Display, TEXT("Round %i/%i Begin:"), CurrentRound,GameData.RoundNum);
}
void ABSGameModeBase::GameTimerUpdate()
{
	if(--RoundCountDown != 0)
	{
		return;
	}
	
	UE_LOG(LogGameMode, Display, TEXT("Round %i Ends:"), CurrentRound);
	GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
	if(CurrentRound + 1<= GameData.RoundNum)
	{
		CurrentRound++;
		StartRound();
	}
	else
	{
		GameOver();
	}
}
void ABSGameModeBase::SpawnBots()
{
	if (!GetWorld())
	{
		return;
	}
	for (int i = 0; i < GameData.PlayerNum - 1; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto BSAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(BSAIController);
	}
}
void ABSGameModeBase::GameOver()
{
	UE_LOG(LogGameMode, Display, TEXT("------ GAME OVER ------"));
	LogInfo();

	for(const auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if(!Pawn)
		{
			continue;
		}
		Pawn->TurnOff();
		Pawn->DisableInput(nullptr);
	}
}
void ABSGameModeBase::ResetPlayers()
{
	if(!GetWorld())
	{
		return;	
	}
	for(auto It = GetWorld()->GetControllerIterator();It; ++It)
	{
		const auto ItController = It->Get();
		ResetOnePlayer(ItController);
	}
}
void ABSGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}
void ABSGameModeBase::CreateTeamInfo() const
{
	if(!GetWorld())
	{
		return;	
	}
	int32 TeamID = 0;
	for(auto It = GetWorld()->GetControllerIterator();It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller)
		{
			continue;
		}
		const auto PlayerState = Cast<ABSPlayerState>(Controller->PlayerState);
		if(!PlayerState)
		{
			continue;
		}

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);
		if(!GameData.TeamsData.IsEmpty())
		{
			TeamID = (TeamID + 1) % GameData.TeamsData.Num(); 
		}
	}
	
} 
void ABSGameModeBase::SetPlayerColor(const AController* Controller)
{
	if(!Controller)
	{
		return;
	}

	const auto Character = Cast<ABSBaseCharacter>(Controller->GetPawn());
	if(!Controller)
	{
		return;
	}

	const auto PlayerState = Cast<ABSPlayerState>(Controller->PlayerState);
	if(!PlayerState)
	{
		return;
	}

	Character->SetPlayerColor(PlayerState->GetTeamColor());
} 
FLinearColor ABSGameModeBase::DetermineColorByTeamID(int32 ID) const
{
	if (ID < GameData.TeamsData.Num() && ID >= 0)
	{
		return GameData.TeamsData[ID].TeamColor;
	}
	UE_LOG(LogGameMode, Warning, TEXT("Team color not found, ID: %i invalid, set to default: %s"), ID, *GameData.DefaultTeamData.TeamColor.ToString());
	return GameData.DefaultTeamData.TeamColor;
}
void ABSGameModeBase::StartRespawn(AController* Controller) const
{
	if(!CanRespawn())
	{
		return;
	}
	const auto RespawnComponent = BSCoreUtils::GetActorComponent<UBSRespawnComponent>(Controller);
	if(!RespawnComponent)
	{
		return;
	}

	RespawnComponent->Respawn(GameData.RespawnRate);
	
}
void ABSGameModeBase::LogInfo() const
{
	if(!GetWorld())
	{
		return;
	}
	for(auto It = GetWorld()->GetControllerIterator();It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller)
		{
			return;
		}

		const auto PlayerState = Cast<ABSPlayerState>(Controller->PlayerState);
		if(!PlayerState)
		{
			return;
		}

		PlayerState->LogInfo();
	}
	
		
}