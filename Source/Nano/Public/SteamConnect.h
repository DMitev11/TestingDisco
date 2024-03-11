#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "SteamConnect.generated.h"

/**
 *
 */
UCLASS()
class NANO_API USteamConnect : public UGameInstance
{
	GENERATED_BODY()

public:
	USteamConnect();

protected:
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	IOnlineSessionPtr SessionInterface;

	virtual void Init() override;

	virtual void OnCreateSessionComplete(FName SessionName, bool Succeeded);
	virtual void OnFindSessionComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable)
	void CreateServer();

	UFUNCTION(BlueprintCallable)
	void JoinServer();

	UFUNCTION(BlueprintCallable)
	void DestroyServer();
};
