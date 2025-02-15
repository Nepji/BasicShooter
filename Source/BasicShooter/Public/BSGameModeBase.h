// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "BSGameModeBase.generated.h"

class AAIController;
/**
 *
 */
UCLASS()
class BASICSHOOTER_API ABSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	FOnMatchStateChangedSignature OnMatchStateChanged;
	
public:
	ABSGameModeBase();

	void Killed(AController* KillerController, AController* VictimController, const AController* AssistantController = nullptr);
	bool CanRespawn() const;

	int32 GetRoundCountDown() const;
	int32 GetCurrentMatchRound() const;
	int32 GetMatchRoundsCount() const;
	void RespawnRequest(AController* Controller);

	virtual bool ClearPause() override;

protected:
	UPROPERTY(EditDefaultsOnly, Blueprintable, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Blueprintable, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Blueprintable, Category = "Game")
	FGameData GameData;

protected:
	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;


private:
	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimerHandle;
	EBSMatchState MatchState = EBSMatchState::WaitingToStart;
private:
	void StartRound();
	void GameTimerUpdate();
	void SpawnBots();
	void GameOver();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamInfo() const;
	static void SetPlayerColor(const AController* Controller);
	FLinearColor DetermineColorByTeamID(int32 ID) const;

	void StartRespawn(AController* Controller) const;

	void LogInfo() const;

	void SetMatchState(EBSMatchState State);
};
