// : LeaveMeAlone Game by Netologiya. All RightsReserved.

#include "LMAGameMode.h"
#include "Player/LMAPlayerController.h"
#include "Player/LMADefaultCharacter.h"

ALMAGameMode::ALMAGameMode() {
	DefaultPawnClass = ALMADefaultCharacter::StaticClass();
	PlayerControllerClass = ALMAPlayerController::StaticClass();
}
