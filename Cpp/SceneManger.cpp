#include "../Header/Camera.h"
#include "../Header/Characters.h"
#include "../Header/Collisions.h"
#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/LoadingManager.h"
#include "../Header/MapManager.h"
#include "../Header/Master.h"
#include "../Header/ObjectManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TimeManager.h"
#include "../Header/UIs.h"

// コンストラクタ
SceneManager::SceneManager()
: meNowScene(SCENE_NAME::START)
, meNextScene(SCENE_NAME::TITLE)
, mpLoadingManager(nullptr)
{
}
// デストラクタ
SceneManager::~SceneManager()
{
}

// 初期化
void SceneManager::Initilize()
{
	mpLoadingManager = Master::mpLoadingManager;
}

// シーン移動するかを確認する
void SceneManager::CheckNextScene()
{
	if ((meNowScene != meNextScene) && ((mpLoadingManager->GetLoadingFlag() & (unsigned int)LOADING_FLAG::SCENE_CHANGE) == 0))
	{
		mpLoadingManager->SetLoadingFlag(LOADING_FLAG::SCENE_CHANGE);
	}
}

// 次のシーンに移動する
void SceneManager::NewSceneProcess()
{
	Master::mpGameManager->GetObjectManager()->SetDeleteSceneObject(meNowScene);

	meNowScene = meNextScene;

	switch (meNowScene)
	{
	case SCENE_NAME::TITLE:
	{
		Master::mpGameManager->GetMapManager()->Initilize();
		TitleUI* title = new TitleUI();
		title->Initilize();
	}
		break;

	case SCENE_NAME::SELECT:
	{
		SetPlayerDataUI* select = new SetPlayerDataUI();
		select->Initilize();
	}
		break;

	case SCENE_NAME::RE_GAME:
		meNextScene = SCENE_NAME::GAME;
		meNowScene = meNextScene;

	case SCENE_NAME::GAME:
	{
		Master::mpGameManager->GetCamera()->Initilize();
		Master::mpGameManager->GetCamera()->SetCameraMode(CAMERA_MODE::PLAYERS_MIDDLE_MOVE);

		Master::mpGameManager->GetMapManager()->Initilize();

		PlayerManager* playerManager = new PlayerManager(5);
		playerManager->Initilize();

		/*
		PlayerBase* test1 = new PlayerBase(0);
		test1->Initilize();//*/

		/*
		PlayerBase* test2 = new PlayerBase(1);
		test2->Initilize();//*/
		
		/*
		PlayerBase* test3 = new PlayerBase(2);
		test3->Initilize();//*/
		
		
		/*
		EnemyBase* test4 = new EnemyBase(VECTOR_2D::GetFloatVec(10.0f, 10.0f));
		test4->Initilize();//*/

		CameraCollision* cameraCollision = new CameraCollision();
		cameraCollision->Initilize();

		Master::mpDataManager->SetGameStartTime(Master::mpTimeManager->GetGameTime());
	}
		break;
	}
}