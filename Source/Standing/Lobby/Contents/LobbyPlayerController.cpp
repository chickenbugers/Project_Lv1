// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/Contents/LobbyPlayerController.h"
#include "Lobby/Contents/LobbyPlayerState.h"
#include "Lobby/Contents/LobbyGameMode.h"
#include "Kismet/GameplayStatics.h"

void ALobbyPlayerController::Server_HandleReadyButton_Implementation()
{
	if (HasAuthority() == false)
		return;

	ALobbyPlayerState* LobbyPlayerState = GetPawn()->GetPlayerState<ALobbyPlayerState>();
	if (LobbyPlayerState)
	{
		LobbyPlayerState->Multicast_Ready();
	}

	ALobbyGameMode* LobbyGameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(this));
	if(LobbyGameMode)
	{
		LobbyGameMode->TryStartGame();
	}
}

void ALobbyPlayerController::Server_HandleChangeNickName_Implementation(const FText& InNickName)
{
	if (HasAuthority() == false)
		return;

	ALobbyPlayerState* LobbyPlayerState = GetPawn()->GetPlayerState<ALobbyPlayerState>();
	if (LobbyPlayerState)
	{
		LobbyPlayerState->NickName = InNickName;
	}
}