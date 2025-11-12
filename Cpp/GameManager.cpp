#include "../Header/Camera.h"
#include "../Header/GameManager.h"
#include "../Header/KeyState.h"
#include "../Header/LoadingManager.h"
#include "../Header/MapManager.h"
#include "../Header/Master.h"
#include "../Header/ObjectManager.h"
#include "../Header/ResourceManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TargetDatas.h"
#include "../Header/TimeManager.h"

extern void Render();

// コンストラクタ
GameManager::GameManager()
: mbEndFlag(false)
, mpCamera(nullptr)
, mpObjectManager(nullptr)
, mpMapManager(nullptr)
, mpTargetDatas(nullptr)
{
}
// デストラクタ
GameManager::~GameManager()
{
}

// 初期化
void GameManager::Initilize()
{
    // ローディングマネージャー初期化
    Master::mpLoadingManager->Initilize();
    // シーンマネージャー初期化
    Master::mpSceneManager->Initilize();

    // カメラ生成
    mpCamera = new Camera();
    mpCamera->Initilize();

    // 初期化
    Master::mpResourceManager->Initilize();

    // オブジェクトマネージャー生成
    mpObjectManager = new ObjectManager();
    mpObjectManager->Initilize();

    // マップマネージャー生成
    mpMapManager = new MapManager();

    mpTargetDatas = new TargetDatas();

    // 時間設定
    Master::mpTimeManager->Initilize();
    // 16.66msで設定(仮)
    //Master::mpTimeManager->SetOneFrame((int)(1000.0f / 60.0f));

    // シーンを移動する
    Master::mpSceneManager->CheckNextScene();
}

// 終了処理
void GameManager::Finailize()
{
    mpMapManager->Finalize();
    mpObjectManager->Finalize();

    delete mpTargetDatas;
    delete mpMapManager;
    delete mpObjectManager;
    delete mpCamera;
}

// 更新
void GameManager::Update()
{
    // キー状態更新
    Master::mpKeyState->Update();

    // カメラの更新
    mpCamera->Update();

    // オブジェクト更新
    mpObjectManager->Update();
    mpObjectManager->LastUpdate();

    // マップ更新(シーンマネージャーにオブジェクトベース化して移す)
    mpMapManager->Update();
}

// 描画
void GameManager::Draw()
{
    // 描画開始
    Master::mpResourceManager->StartDraw();

    // マップ描画
    mpMapManager->Draw();

    Render();

    // オブジェクト描画
    mpObjectManager->Draw();
    mpObjectManager->LastDraw();

    // 描画終了
    Master::mpResourceManager->EndDraw();
}