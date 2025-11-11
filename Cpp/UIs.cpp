#include <vector>

#include <DirectXMath.h>

#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/FSM.h"
#include "../Header/KeyState.h"
#include "../Header/Macro.h"
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
, mnResourceID(-1)
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

	mnResourceID = Master::mpResourceManager->AddResource(L"Resource/Back.png");
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
	Master::mpResourceManager->DrawSprite(Master::mpDataManager->GetDisplaySize().X * 0.5f, Master::mpDataManager->GetDisplaySize().Y * 0.5f,
		Master::mpDataManager->GetDisplaySize().X * 0.9f, Master::mpDataManager->GetDisplaySize().Y * 0.9f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceID, MIDDLE_FLAG);

	mpFSM->Draw(this);
}

/*選択決定時処理*/
void SetPlayerDataUI::DecisionProcess()
{
	++mnSelectPlayerNumber;
	if (mnSelectPlayerNumber < Master::mpDataManager->GetPlayerCount())
	{
		mpFSM->GetCurrentState()->OnExit(this);
		mpFSM->SetCurrentState(SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT, this);
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

/*選択肢上変更(プラス)*/
void SetPlayerDataUI::UpKeyDown()
{
	if (CheckUp_Frame())
	{
		++mnSelectNumber;
		if (mnSelectNumber >= mnMaxSelectNumber)
		{
			mnSelectNumber = 0;
		}
	}
}

/*選択肢下変更(マイナス)*/
void SetPlayerDataUI::DownKeyUp()
{
	if (CheckDown_Frame())
	{
		--mnSelectNumber;
		if (mnSelectNumber < 0)
		{
			mnSelectNumber = mnMaxSelectNumber - 1;
		}
	}
}


/*--------------------------------------------------------------------------------------------------------------
* 【リザルトUI】
*/
/*コンストラクタ*/
ResultUI::ResultUI()
: UIBase(1, true, true)
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

	if (mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::L) && mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::R))
	{
		Master::mpGameManager->SetEndFlag(true);
	}

	if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::B))
	{
		Master::mpSceneManager->SetNextScene(SCENE_NAME::TITLE);
	}
}

/*UI描画*/
void ResultUI::UIDraw()
{
	Master::mpResourceManager->DrawString("RESULT", XMFLOAT2(90.0f, 90.0f), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

/*選択決定時処理*/
void ResultUI::DecisionProcess()
{
	Master::mpSceneManager->SetNextScene(SCENE_NAME::RESULT);
}


/*--------------------------------------------------------------------------------------------------------------
* 【プレイヤーコントローラー設定用UI】
*/
/*コンストラクタ*/
PlayerControllerUI::PlayerControllerUI()
: UIBase(1, true)
, mnStartFlag(false)
, mpDataManager(nullptr)
, mnBlinkTime(0)
{
	mnResourceIDs.clear();

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

	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/WhiteBack.jpg"));
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/Frame.png"));
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/Controller/3.png"));
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/Controller/0.png"));
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/Controller/1.png"));
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/Controller/2.png"));
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
		if ((mnBlinkTime + 40) < Master::mpTimeManager->GetFrame())
		{
			mnBlinkTime = Master::mpTimeManager->GetFrame() + 40;
		}

		if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::B))
		{
			if (mnSelectNumber == 0)
			{
				mnStartFlag = false;
				DeleteUINumber();
			}
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
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.5f,
			mpDataManager->GetDisplaySize().X * 1.0f, mpDataManager->GetDisplaySize().Y * 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[0], MIDDLE_FLAG);

		Master::mpResourceManager->DrawString(std::to_string(mnSelectNumber), XMFLOAT2(150.0f, 150.0f), D2D1_DRAW_TEXT_OPTIONS_NONE);

		for (int i = 0; i < mnMaxSelectNumber; i++)
		{
			Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.15f, mpDataManager->GetDisplaySize().Y * 0.3f,
				mpDataManager->GetDisplaySize().X * 0.15f, mpDataManager->GetDisplaySize().Y * 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[1], MIDDLE_FLAG);
		}

		if (mnSelectNumber >= mnMaxSelectNumber)
		{
			for (int i = 0; i < mnSelectNumber; i++)
			{
				if (mnBlinkTime < Master::mpTimeManager->GetFrame())
				{
					Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.5f,
						mpDataManager->GetDisplaySize().X * 1.0f, mpDataManager->GetDisplaySize().Y * 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[3], MIDDLE_FLAG);
				}
				else
				{
					Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.5f,
						mpDataManager->GetDisplaySize().X * 1.0f, mpDataManager->GetDisplaySize().Y * 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[5], MIDDLE_FLAG);
				}
			}
		}
		else
		{
			for (int i = 0; i < mnSelectNumber; i++)
			{
				Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.5f,
					mpDataManager->GetDisplaySize().X * 1.0f, mpDataManager->GetDisplaySize().Y * 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[2], MIDDLE_FLAG);
			}

			if (mnBlinkTime < Master::mpTimeManager->GetFrame())
			{
				Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.5f,
					mpDataManager->GetDisplaySize().X * 1.0f, mpDataManager->GetDisplaySize().Y * 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[3], MIDDLE_FLAG);
			}
			else
			{
				Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.5f,
					mpDataManager->GetDisplaySize().X * 1.0f, mpDataManager->GetDisplaySize().Y * 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[4], MIDDLE_FLAG);
			}
		}
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