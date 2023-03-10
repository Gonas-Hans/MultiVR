// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSessions/MultiVRGameSession.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

void AMultiVRGameSession::FindSessions(TSharedPtr<const FUniqueNetId> UserID, bool bIsLAN, bool bIsPresence)
{
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if ()
	}
}
