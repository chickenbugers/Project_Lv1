// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/UI/LobbyUserWidget.h"
#include "Lobby/Contents/LobbyPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LobbyWidget.h"

void ULobbyUserWidget::SetInfo(ALobbyPlayerState* InPlayerState)
{
	PlayerState = InPlayerState;

	RefreshUI();
}

void ULobbyUserWidget::RefreshUI()
{
	if (PlayerState == nullptr) 
		return;

	bool IsLocalPlayer = false;

	APlayerController* PlayerController = PlayerState->GetPlayerController();
	if(PlayerController)
		IsLocalPlayer = PlayerController->IsLocalController();

	bool IsReady = PlayerState->Ready;
	bool IsServer = UKismetSystemLibrary::IsServer(this);

	//Hidden
	Txt_Ready->SetVisibility(ESlateVisibility::Hidden);
	Txt_PlayerName->SetVisibility(ESlateVisibility::Hidden);
	Editable_PlayerName->SetVisibility(ESlateVisibility::Hidden);
	Btn_Ready->SetVisibility(ESlateVisibility::Hidden);
	Btn_KickPlayer->SetVisibility(ESlateVisibility::Hidden);

	if(IsReady)
		Txt_Ready->SetVisibility(ESlateVisibility::Visible);

	if (IsLocalPlayer && IsReady == false)
		Btn_Ready->SetVisibility(ESlateVisibility::Visible);

	if (IsServer && IsLocalPlayer == false)
		Btn_KickPlayer->SetVisibility(ESlateVisibility::Visible);

	Editable_PlayerName->SetText(PlayerState->NickName);
	Editable_PlayerName->SetVisibility(ESlateVisibility::Visible);

	if(IsReady)
		Editable_PlayerName->SetIsReadOnly(true);
	else
		Editable_PlayerName->SetIsReadOnly(!IsLocalPlayer);
}