// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class STANDING_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Ready();

public:
	//BP »£√‚
	UFUNCTION(BlueprintImplementableEvent)
	void BP_RefreshLobbyUI();

	UFUNCTION(BlueprintCallable)
	void RefreshLobbyUI();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool Ready;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_NickNameChange)
	FText NickName;

private:
	UFUNCTION()
	void OnRep_NickNameChange();
};
