/**
* Copyright (C) 2017-2022 eelDev AB
*
* Official Steamworks Documentation: https://partner.steamgames.com/doc/api/ISteamAppList
*/

#pragma once

#include "UObject/NameTypes.h"
#include <OnlineSubsystemTypes.h>
#include <Interfaces/OnlinePresenceInterface.h>
#include "SteamCoreSharedTypes.generated.h"


#ifndef STEAMCORE_SUBSYSTEM
#define STEAMCORE_SUBSYSTEM FName(TEXT("STEAMCORE"))
#endif

#ifdef _MSC_VER
#define STEAM_SDK_IGNORE_REDUNDANCY_START \
__pragma(warning(push)) \
__pragma(warning(disable: 6287)) 

#define STEAM_SDK_IGNORE_REDUNDANCY_END \
__pragma(warning(pop))
#else
#define STEAM_SDK_IGNORE_REDUNDANCY_START
#define STEAM_SDK_IGNORE_REDUNDANCY_END
#endif

namespace FNetworkProtocolTypes
{
 STEAMCORESHARED_API extern const FLazyName SteamCore;
 STEAMCORESHARED_API extern const FLazyName SteamCoreSocketsP2P;
 STEAMCORESHARED_API extern const FLazyName SteamCoreSocketsIP;
}

UENUM(BlueprintType)
enum class EOnlineFriendSteamCorePresenceState : uint8
{
 /** User is offline */
 Offline,
 /** User is online */
 Online,
 /** User is away */
 Away,
 /** User is away for >2 hours (can change depending on platform) */
 ExtendedAway,
 /** User is in do not disturb mode */
 DoNotDisturb,
 /** Default */
 Unknown
};
USTRUCT(BlueprintType)
struct STEAMCORESHARED_API FOnlineUserPresenceSteamCoreBlueprint
{
 GENERATED_BODY()
	
public:
 FOnlineUserPresenceSteamCoreBlueprint()
  : bIsOnline(false)
  , bIsPlaying(false)
  , bIsPlayingThisGame(false)
  , bIsJoinable(false)
  , bHasVoiceSupport(false)
  , PresenceState(EOnlineFriendSteamCorePresenceState::Offline)
 {
 }
 FOnlineUserPresenceSteamCoreBlueprint(const FOnlineUserPresence& Presence)
  : bIsOnline(Presence.bIsOnline)
  , bIsPlaying(Presence.bIsPlaying)
  , bIsPlayingThisGame(Presence.bIsPlayingThisGame)
  , bIsJoinable(Presence.bIsJoinable)
  , bHasVoiceSupport(Presence.bHasVoiceSupport)
  , PresenceState(static_cast<EOnlineFriendSteamCorePresenceState>(Presence.Status.State))
 {
 }
public:
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 bool bIsOnline;
	
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 bool bIsPlaying;
	
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 bool bIsPlayingThisGame;
	
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 bool bIsJoinable;
	
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 bool bHasVoiceSupport;
	
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 FDateTime LastOnline;
	
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 EOnlineFriendSteamCorePresenceState PresenceState;
};
USTRUCT(BlueprintType)
struct STEAMCORESHARED_API FOnlineFriendSteamCoreBlueprint
{
 GENERATED_BODY()
	
public:
 FOnlineFriendSteamCoreBlueprint()
 {
 }
 FOnlineFriendSteamCoreBlueprint(const FOnlineFriend& Friend)
  : DisplayName(Friend.GetDisplayName())
  , RealName(Friend.GetRealName())
  , Presence(Friend.GetPresence())
  , SteamId(Friend.GetUserId()->ToString())
 {
 }
public:
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 FString DisplayName;
	
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 FString RealName;
	
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 FOnlineUserPresenceSteamCoreBlueprint Presence;
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
 FString SteamId;
};