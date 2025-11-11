#include <vector>

#include "../Header/IState.h"

#include "../Header/DataManager.h"
#include "../Header/KeyState.h"
#include "../Header/Master.h"
#include "../Header/ResourceManager.h"

IState_SetPlayerDataUI::IState_SetPlayerDataUI()
{
	mpDataManager = Master::mpDataManager;

	mpKeyState = Master::mpKeyState;

	mpResourceManager = Master::mpResourceManager;

	mnResourceIDs.clear();
}

IState_SetPlayerDataUI::~IState_SetPlayerDataUI()
{
	for (int i = 0; i < mnResourceIDs.size(); i++)
	{
		Master::mpResourceManager->SubResource(mnResourceIDs[i]);
	}
}