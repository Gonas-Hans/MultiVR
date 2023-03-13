// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "GameFramework/GameSession.h"
#include "MultiVRGameSession.generated.h"

/**
 * 
 */
UCLASS()
class MULTIVR_API AMultiVRGameSession : public AGameSession
{
	GENERATED_BODY()

public:
	/**
	 * @param UserId Юзер, инициирующий поиск.
	 * @param bIsLAN Если ищем в локальной сети
	 * @param bIsPresence Будет поиск сессий с тем же флагом.                                                   
	 * Используется с сервисами вроде стим'а,
	 * чтобы позволить игрокам подключаться друг к другу через список друзей, к примеру.  
	 */
	void FindSessions(TSharedPtr<const FUniqueNetId> UserID, bool bIsLAN, bool bIsPresence);

private:
	TSharedPtr<FOnlineSessionSearch> SearchSettings;

	
};
