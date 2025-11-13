#include <windows.h>

#include "../Header/EndManager.h"
#include "../Header/GameManager.h"
#include "../Header/Master.h"
#include "../Header/ObjectManager.h"
#include "../Header/ResourceManager.h"

// コンストラクタ
EndManager::EndManager()
: mbEndFlag(false)
{
}

//デストラクタ
EndManager::~EndManager()
{
}

/*終了フラグ取得*/
bool EndManager::GetEndFlag(MSG msg)
{
	bool endFlag = false;

	endFlag |= (WM_QUIT == msg.message);

	endFlag |= ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0);

	endFlag |= Master::mpGameManager->GetEndFlag();

	endFlag |= Master::mpResourceManager->GetEndFlag();

	endFlag |= mbEndFlag;

	return endFlag;
}

/*終了フラグ取得*/
bool EndManager::GetEndFlag()
{
	bool endFlag = false;

	endFlag |= ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0);

	endFlag |= Master::mpGameManager->GetEndFlag();

	endFlag |= Master::mpResourceManager->GetEndFlag();

	endFlag |= mbEndFlag;

	return endFlag;
}