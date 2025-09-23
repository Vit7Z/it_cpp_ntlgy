// : LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LMAPlayerController.generated.h"

/**
 *
 */
UCLASS()
class LEAVEMEALONE_API ALMAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALMAPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//6
	virtual void BeginSpectatingState() override;
};
