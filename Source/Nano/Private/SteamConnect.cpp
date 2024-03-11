#include "SteamConnect.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

USteamConnect::USteamConnect()
{
}

void USteamConnect::Init()
{
    Super::Init();

    if (IOnlineSubsystem *Subsystem = IOnlineSubsystem::Get())
    {
        SessionInterface = Subsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &USteamConnect::OnCreateSessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &USteamConnect::OnFindSessionComplete);
            SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &USteamConnect::OnJoinSessionComplete);
        }
    }
}

void USteamConnect::OnCreateSessionComplete(FName SessionName, bool Succeeded)
{
    if (Succeeded)
    {
        GetWorld()->ServerTravel("/Game/Maps/L_CameraGym?listen");
    }
}

void USteamConnect::OnFindSessionComplete(bool Succeeded)
{
    if (Succeeded)
    {
        TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;

        if (SearchResults.Num())
        {
            SessionInterface->JoinSession(0, FName("Testing Disco"), SearchResults[0]);
        }
        else
        {
            CreateServer();
        }
    }
}

void USteamConnect::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    if (APlayerController *PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        FString JoinAddress = "";
        SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
        if (JoinAddress != "")
        {
            PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
        }
    }
}

void USteamConnect::CreateServer()
{
    auto *subsystem = IOnlineSubsystem::Get();
    if (!subsystem)
        return;

    auto sessions = subsystem->GetSessionInterface();
    if (!sessions.IsValid())
        return;

    FOnlineSessionSettings SessionSettings;
    SessionSettings.bAllowJoinInProgress = true;
    SessionSettings.NumPublicConnections = 5;
    SessionSettings.bIsLANMatch = false;
    SessionSettings.bUsesPresence = true;

    SessionInterface->CreateSession(0, FName("Testing Disco"), SessionSettings);
}

void USteamConnect::JoinServer()
{
    auto *subsystem = IOnlineSubsystem::Get();
    if (!subsystem)
        return;

    auto sessions = subsystem->GetSessionInterface();
    FNamedOnlineSession *validSession = sessions->GetNamedSession("Testing Disco");
    if (sessions.IsValid())
    {
        SessionSearch = MakeShareable(new FOnlineSessionSearch());
        SessionSearch->bIsLanQuery = false;
        SessionSearch->MaxSearchResults = 10000;
        auto ret = sessions->FindSessions(0, SessionSearch.ToSharedRef());
        // found session
        if (ret)
            return;
    }

    this->CreateServer();
}

void USteamConnect::DestroyServer()
{
    auto *subsystem = IOnlineSubsystem::Get();
    if (!subsystem)
        return;

    auto sessions = subsystem->GetSessionInterface();
    sessions->DestroySession("Testing Disco");
}