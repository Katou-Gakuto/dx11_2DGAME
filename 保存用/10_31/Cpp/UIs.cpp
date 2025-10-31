#include <vector>

#include <DirectXMath.h>

#include "../Header/DataManager.h"
#include "../Header/FSM.h"
#include "../Header/KeyState.h"
#include "../Header/Master.h"
#include "../Header/ObjectBases.h"
#include "../Header/ResourceManager.h"
#include "../Header/SceneManager.h"
#include "../Header/State_SetPlayerDataUI.h"
#include "../Header/TemplateData.h"
#include "../Header/UIs.h"

using namespace DirectX;


/*--------------------------------------------------------------------------------------------------------------
* 【タイトルUI】
*/
/*コンストラクタ*/
TitleUI::TitleUI()
: UIBase(1, true)
{
}

/*デストラクタ*/
TitleUI::~TitleUI()
{
}

/*UI初期化*/
void TitleUI::UIInitilize()
{
}

/*UI終了*/
void TitleUI::UIFinalize()
{
}

/*UI更新*/
void TitleUI::UIUpdate()
{
	DefaultDecision();
}

/*UI描画*/
void TitleUI::UIDraw()
{
	Master::mpResourceManager->DrawString("TITLE", XMFLOAT2(90.0f, 90.0f), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

/*選択決定時処理*/
void TitleUI::DecisionProcess()
{
	Master::mpSceneManager->SetNextScene(SCENE_NAME::SELECT);
}

/*--------------------------------------------------------------------------------------------------------------
* 【プレイヤーデータ設定UI】
*/
/*コンストラクタ*/
SetPlayerDataUI::SetPlayerDataUI()
: UIBase(5, true)
, mnPlayerCount(0)
, mnSelectPlayerNumber(0)
, mnProcessNumber(0)
, mpSetPlayerController(nullptr)
, mpFSM(nullptr)
{
}

/*デストラクタ*/
SetPlayerDataUI::~SetPlayerDataUI()
{
	delete mpFSM;
}

/*UI初期化*/
void SetPlayerDataUI::UIInitilize()
{
	mpSetPlayerController = new PlayerControllerUI();
	mpSetPlayerController->Initilize();

	mpFSM = new FSM_SelectUI();
	mpFSM->RegisterState(SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER, new SPDUIPlayerNumber());
	mpFSM->RegisterState(SET_PLAYER_DATA_UI_STATE_CONTROLLER_SELECT, new SPDUIControllerSelect());
	mpFSM->RegisterState(SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT, new SPDUICharacterSelect());
	mpFSM->RegisterState(SET_PLAYER_DATA_UI_STATE_NAME_SET, new SPDUINameSet());
	mpFSM->SetCurrentState(SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER, this);
}

/*UI終了*/
void SetPlayerDataUI::UIFinalize()
{
}

/*UI更新*/
void SetPlayerDataUI::UIUpdate()
{
	mpFSM->Init();
	CheckMouse();
	CheckKeyboard();
	CheckController();
	CheckKeyboard_Controller();
	//switch (mnProcessNumber)
	//{
	//case 0:// プレイヤー数決定

	//	if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::A, false) || mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER))
	//	{
	//		++mnProcessNumber;
	//		mnPlayerCount = mnSelectNumber + 1;
	//		for (int i = 0; i < mnPlayerCount; i++)
	//		{
	//			mstPlayerDatas.push_back(PlayerData());
	//		}
	//	}
	//	break;

	//case 1:// コントローラー割り当て(全プレイヤー分)
	//{
	//	++mnProcessNumber;

	//	std::vector<int*>setControllerNumber;
	//	setControllerNumber.clear();
	//	setControllerNumber.reserve(mnPlayerCount);
	//	for (int i = 0; i < mnPlayerCount; i++)
	//	{
	//		setControllerNumber.push_back(&mstPlayerDatas[i].keyNumber);
	//	}

	//	mpSetPlayerController->SetControllerStart(setControllerNumber);
	//}
	//	break;

	//case 2:// キャラ選択
	//	break;

	//case 3:// 名前決定
	//	break;
	//}


	//DefaultDecision();
}

/*UI描画*/
void SetPlayerDataUI::UIDraw()
{
	Master::mpResourceManager->DrawString("SELECT", XMFLOAT2(90.0f, 90.0f), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

/*選択決定時処理*/
void SetPlayerDataUI::DecisionProcess()
{
	++mnSelectPlayerNumber;
	if (mnSelectPlayerNumber < mnPlayerCount)
	{
		mnProcessNumber = 2;
	}
	else
	{
		Master::mpSceneManager->SetNextScene(SCENE_NAME::GAME);
	}
}

/*マウスが反応した時に実行する*/
void SetPlayerDataUI::MouseProcess()
{
	mpFSM->MouseUpdate(this);
}

/*キーボードが反応した時に実行する*/
void SetPlayerDataUI::KeyboardProcess()
{
	mpFSM->KeyboardUpdate(this);
}

/*コントローラーが反応した時に実行する*/
void SetPlayerDataUI::ControllerProcess()
{
	mpFSM->ControllerUpdate(this);
}

/*キーボードかコントローラーが反応した時に実行する*/
void SetPlayerDataUI::Keyboard_ControllerProcess()
{
	mpFSM->Keyboard_And_ControllerUpdate(this);
}


/*--------------------------------------------------------------------------------------------------------------
* 【リザルトUI】
*/
/*コンストラクタ*/
ResultUI::ResultUI()
: UIBase(1, true)
{
}

/*デストラクタ*/
ResultUI::~ResultUI()
{
}

/*UI初期化*/
void ResultUI::UIInitilize()
{
}

/*UI終了*/
void ResultUI::UIFinalize()
{
}

/*UI更新*/
void ResultUI::UIUpdate()
{
	DefaultDecision();
}

/*UI描画*/
void ResultUI::UIDraw()
{
	Master::mpResourceManager->DrawString("RESULT", XMFLOAT2(90.0f, 90.0f), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

/*選択決定時処理*/
void ResultUI::DecisionProcess()
{
	Master::mpSceneManager->SetNextScene(SCENE_NAME::GAME);
}


/*--------------------------------------------------------------------------------------------------------------
* 【プレイヤーコントローラー設定用UI】
*/
/*コンストラクタ*/
PlayerControllerUI::PlayerControllerUI()
: UIBase(1, true)
, mnStartFlag(false)
, mpDataManager(nullptr)
{
	mpDataManager = Master::mpDataManager;

	memset(mnSetPlayerKey, -1, sizeof(int) * 5);
}

/*デストラクタ*/
PlayerControllerUI::~PlayerControllerUI()
{
}

/*UI初期化*/
void PlayerControllerUI::UIInitilize()
{
	memset(mnSetPlayerKey, -1, sizeof(int) * 5);
}

/*UI終了*/
void PlayerControllerUI::UIFinalize()
{
}

/*UI更新*/
void PlayerControllerUI::UIUpdate()
{
	if (mnStartFlag)
	{
		if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::B))
		{
			mnSelectNumber = mnMaxSelectNumber + 1;
			DecisionProcess();
		}

		if (mnSelectNumber >= mnMaxSelectNumber)
		{
			for (int i = 0; i < mnMaxSelectNumber; i++)
			{
				if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::RIGHT, mnSetPlayerKey[i]))
				{
					mnSelectNumber = mnMaxSelectNumber;
				}
				if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::LEFT, mnSetPlayerKey[i]))
				{
					mnSelectNumber = mnMaxSelectNumber + 1;
				}
			}

			DefaultDecision();
		}
		else
		{
			for (int i = 0; i < (int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER; i++)
			{
				if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::L, i) && mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::R, i))
				{
					bool setFlag = true;
					for (int j = 0; j < mnSelectNumber; j++)
					{
						if (i == mnSetPlayerKey[j])
						{
							setFlag = false;
							break;
						}
					}

					if (setFlag)
					{
						mnSetPlayerKey[mnSelectNumber] = i;
						mnSelectNumber++;
						break;
					}
				}
			}
		}
	}
}

/*UI描画*/
void PlayerControllerUI::UIDraw()
{
	if (mnStartFlag)
	{

	}
}

/*プレイヤーキー設定開始*/
void PlayerControllerUI::SetControllerStart()
{
	mnSelectNumber = 0;
	mnMaxSelectNumber = (int)mpDataManager->GetPlayerData().size();
	mnStartFlag = true;

	SetUINumber();
}

/*選択決定時処理*/
void PlayerControllerUI::DecisionProcess()
{
	if (mnSelectNumber > mnMaxSelectNumber)
	{
		mnSelectNumber = 0;

		for (int i = 0; i < mnMaxSelectNumber; i++)
		{
			mnSetPlayerKey[i] = -1;
		}
	}
	else
	{
		if (!mpDataManager->SetPlayerKeyNumber(mnSetPlayerKey))
		{
			return;
		}

		mnStartFlag = false;
		DeleteUINumber();
	}
}