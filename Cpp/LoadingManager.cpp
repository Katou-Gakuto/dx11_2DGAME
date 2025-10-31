#include "../Header/LoadingManager.h"
#include "../Header/Master.h"
#include "../Header/SceneManager.h"

// コンストラクタ
LoadingManager::LoadingManager()
: mnLoadingFlag(0)
{
}
// デストラクタ
LoadingManager::~LoadingManager()
{
}

// 初期化
void LoadingManager::Initilize()
{
}

// ローディング処理
void LoadingManager::LoadingProcess()
{
	if ((mnLoadingFlag & (unsigned int)LOADING_FLAG::SCENE_CHANGE) != 0)
	{
		Master::mpSceneManager->NewSceneProcess();

		mnLoadingFlag ^= (unsigned int)LOADING_FLAG::SCENE_CHANGE;
	}
}