#include <vector>

#include "../Header/IState.h"

#include "../Header/KeyState.h"
#include "../Header/Master.h"

IState_SetPlayerDataUI::IState_SetPlayerDataUI()
{
	mpKeyState = Master::mpKeyState;

	mnResourceIDs.clear();
}