#include "../Header/Master.h"

#include "../Header/DataManager.h"
#include "../Header/EndManager.h"
#include "../Header/GameManager.h"
#include "../Header/KeyState.h"
#include "../Header/LoadingManager.h"
#include "../Header/ResourceManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TimeManager.h"
#include "../Header/UIManager.h"

// 全削除
void Master::AllDelete()
{
	mpGameManager->Finailize();
	mpResourceManager->Finailize();

	delete mpUIManager;	// UIマネージャー
	delete mpTimeManager;	// タイムマネジャー
	delete mpSceneManager;	// シーンマネージャー
	delete mpResourceManager;	// リソースマネージャー
	delete mpLoadingManager;	// ロードマネージャー
	delete mpKeyState;		// キーステート
	delete mpGameManager;	// ゲームマネージャー
	delete mpEndManager;	// エンドマネジャー
	delete mpDataManager;	// データマネージャー
}