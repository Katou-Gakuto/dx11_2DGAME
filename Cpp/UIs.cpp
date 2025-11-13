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
, mnResourceID(-1)
, mfFontColorAlpha(0.2f)
, mbFontColorAlphaPlusFlag(true)
{
}

/*デストラクタ*/
TitleUI::~TitleUI()
{
}

/*UI初期化*/
void TitleUI::UIInitilize()
{
	mnResourceID = Master::mpResourceManager->AddResource(L"Resource/Back.png");
}

/*UI終了*/
void TitleUI::UIFinalize()
{
	FontData fontData = FontData();
	Master::mpResourceManager->SetFontData(&fontData);
}

/*UI更新*/
void TitleUI::UIUpdate()
{
	if (mbFontColorAlphaPlusFlag)
	{
		mfFontColorAlpha += 0.01f;
		if (mfFontColorAlpha >= 1.0f)
		{
			mfFontColorAlpha = 1.0f;
			mbFontColorAlphaPlusFlag = false;
		}
	}
	else
	{
		mfFontColorAlpha -= 0.01f;
		if (mfFontColorAlpha <= 0.2f)
		{
			mfFontColorAlpha = 0.2f;
			mbFontColorAlphaPlusFlag = true;
		}
	}

	DefaultDecision();
}

/*UI描画*/
void TitleUI::UIDraw()
{
	Master::mpResourceManager->DrawSprite(Master::mpDataManager->GetDisplaySize().X * 0.5f, Master::mpDataManager->GetDisplaySize().Y * 0.5f,
		Master::mpDataManager->GetDisplaySize().X * 0.9f, Master::mpDataManager->GetDisplaySize().Y * 0.9f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceID, MIDDLE_FLAG);

	FontData fontData = FontData();
	fontData.fontSize = 130.0f;
	fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_HEAVY;
	Master::mpResourceManager->SetFontData(&fontData);
	Master::mpResourceManager->DrawString("TEAM BATTLE", XMFLOAT2(Master::mpDataManager->GetDisplaySize().X * 0.5f, Master::mpDataManager->GetDisplaySize().Y * 0.4f), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

	fontData.fontSize = 50.0f;
	fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN;
	fontData.Color.a = mfFontColorAlpha;
	Master::mpResourceManager->SetFontData(&fontData);
	Master::mpResourceManager->DrawString("PRESS A/ENTER TO START", XMFLOAT2(Master::mpDataManager->GetDisplaySize().X * 0.5f, Master::mpDataManager->GetDisplaySize().Y * 0.8f), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);
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
	Master::mpResourceManager->SubResource(mnResourceID);

	delete mpFSM;
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


/*--------------------------------------------------------------------------------------------------------------
* 【リザルトUI】
*/
/*コンストラクタ*/
ResultUI::ResultUI()
: UIBase(1, true, true)
, mpDataManager(nullptr)
, mnGameTime(0)
{
	mnResourceIDs.clear();
}

/*デストラクタ*/
ResultUI::~ResultUI()
{
}

/*UI初期化*/
void ResultUI::UIInitilize()
{
	mpDataManager = Master::mpDataManager;

	mnSelectNumber = 0;
	mnMaxSelectNumber = mpDataManager->GetPlayerCount();
	mnGameTime = (Master::mpTimeManager->GetGameTime() - mpDataManager->GetGameStartTime()) / 1000;

	for (int i = 0; i < mnMaxSelectNumber; i++)
	{
		wchar_t* fileName = nullptr;
		switch (mpDataManager->GetPlayerData(i).characterType)
		{
		case 0:
			fileName = (wchar_t*)L"Resource/Swordsman/pipo-charachip018.png";
			break;
		case 1:
			fileName = (wchar_t*)L"Resource/Swordsman/pipo-charachip018a.png";
			break;
		case 2:
			fileName = (wchar_t*)L"Resource/Swordsman/pipo-charachip018b.png";
			break;
		case 3:
			fileName = (wchar_t*)L"Resource/Swordsman/pipo-charachip018c.png";
			break;
		case 4:
			fileName = (wchar_t*)L"Resource/Swordsman/pipo-charachip018d.png";
			break;
		case 5:
			fileName = (wchar_t*)L"Resource/Swordsman/pipo-charachip018e.png";
			break;
		case 6:
			fileName = (wchar_t*)L"Resource/Swordsman/pipo-charachip018f.png";
			break;
		case 7:
			fileName = (wchar_t*)L"Resource/Swordsman/pipo-charachip018g.png";
			break;
		}
		mnResourceIDs.push_back(Master::mpResourceManager->AddResource(fileName));
	}

	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/ArrowMark.png"));
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/WhiteArrowMark.png"));
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/Back.png"));
}

/*UI終了*/
void ResultUI::UIFinalize()
{
}

/*UI更新*/
void ResultUI::UIUpdate()
{
	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::LEFT, mpDataManager->GetPlayerKeyNumber(0)))
	{
		Decrease();
	}

	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::RIGHT, mpDataManager->GetPlayerKeyNumber(0)))
	{
		Increase();
	}

	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::A, mpDataManager->GetPlayerKeyNumber(0)))
	{
		DecisionProcess();
	}

	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::L, mpDataManager->GetPlayerKeyNumber(0)) && mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::R, mpDataManager->GetPlayerKeyNumber(0)))
	{
		Master::mpGameManager->SetEndFlag(true);
	}

	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::B, mpDataManager->GetPlayerKeyNumber(0)))
	{
		SetDeleteFlag(true);
		Master::mpSceneManager->SetNextScene(SCENE_NAME::TITLE);
	}
}

/*UI描画*/
void ResultUI::UIDraw()
{
	Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.5f,
		mpDataManager->GetDisplaySize().X * 0.9f, mpDataManager->GetDisplaySize().Y * 0.9f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 1], MIDDLE_FLAG);

	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.1325f, mpDataManager->GetDisplaySize().Y * 0.14f,
			mpDataManager->GetDisplaySize().X * 0.055f, mpDataManager->GetDisplaySize().Y * 0.07f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 1], MIDDLE_FLAG);

		FontData fontData = FontData();
		fontData.fontSize = 40.0f;
		fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD;
		Master::mpResourceManager->SetFontData(&fontData);
		Master::mpResourceManager->DrawString(std::to_string(mnSelectNumber + 1) + "P", XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.13f, mpDataManager->GetDisplaySize().Y * 0.13f), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

		fontData = FontData();
		Master::mpResourceManager->SetFontData(&fontData);
	}

	Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.51f, mpDataManager->GetDisplaySize().Y * 0.15f,
		mpDataManager->GetDisplaySize().X * 0.35f, mpDataManager->GetDisplaySize().Y * 0.15f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 1], MIDDLE_FLAG);

	FontData fontData = FontData();
	fontData.fontSize = 100.0f;
	fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_HEAVY;
	Master::mpResourceManager->SetFontData(&fontData);
	Master::mpResourceManager->DrawString("RESULT", XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.12f), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

	// タイトル移動　リゲーム
	Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.7825f, mpDataManager->GetDisplaySize().Y * 0.8f,
		mpDataManager->GetDisplaySize().X * 0.295f, mpDataManager->GetDisplaySize().Y * 0.07f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 1], MIDDLE_FLAG);
	Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.7825f, mpDataManager->GetDisplaySize().Y * 0.88f,
		mpDataManager->GetDisplaySize().X * 0.295f, mpDataManager->GetDisplaySize().Y * 0.07f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 1], MIDDLE_FLAG);
	fontData = FontData();
	fontData.fontSize = 30.0f;
	fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD;
	Master::mpResourceManager->SetFontData(&fontData);
	Master::mpResourceManager->DrawString("PRESS A TO RESTART", XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.65f, mpDataManager->GetDisplaySize().Y * 0.77f), D2D1_DRAW_TEXT_OPTIONS_NONE);
	Master::mpResourceManager->DrawString("PRESS B TO TITLE", XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.65f, mpDataManager->GetDisplaySize().Y * 0.85f), D2D1_DRAW_TEXT_OPTIONS_NONE);

	// 右左画像
	if (mpDataManager->GetPlayerCount() >= 2)
	{
			if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::LEFT, mpDataManager->GetPlayerKeyNumber(0)))
		{
			Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.11f, mpDataManager->GetDisplaySize().Y * 0.5f,
				mpDataManager->GetDisplaySize().X * 0.1f, mpDataManager->GetDisplaySize().Y * 0.1f, 0.0f, 0.5f, 0.5f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 3], MIDDLE_FLAG);
		}
		else
		{
			Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.11f, mpDataManager->GetDisplaySize().Y * 0.5f,
				mpDataManager->GetDisplaySize().X * 0.1f, mpDataManager->GetDisplaySize().Y * 0.1f, 0.0f, 0.5f, 0.5f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 2], MIDDLE_FLAG);
		}
		
		if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::RIGHT, mpDataManager->GetPlayerKeyNumber(0)))
		{
			Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.9f, mpDataManager->GetDisplaySize().Y * 0.5f,
				mpDataManager->GetDisplaySize().X * 0.1f, mpDataManager->GetDisplaySize().Y * 0.1f, 0.5f, 1.0f, 0.5f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 3], MIDDLE_FLAG);
		}
		else
		{
			Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.9f, mpDataManager->GetDisplaySize().Y * 0.5f,
				mpDataManager->GetDisplaySize().X * 0.1f, mpDataManager->GetDisplaySize().Y * 0.1f, 0.5f, 1.0f, 0.5f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 2], MIDDLE_FLAG);
		}
	}

	// ゲーム時間
	fontData = FontData();
	fontData.fontSize = 20.0f;
	fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN;
	Master::mpResourceManager->SetFontData(&fontData);
	Master::mpResourceManager->DrawString("GAME TIME : " + std::to_string(mnGameTime) + "sec",
		XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.08f, mpDataManager->GetDisplaySize().Y * 0.87f), D2D1_DRAW_TEXT_OPTIONS_NONE);

	{
		// プレイヤー画像
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.77f,
			mpDataManager->GetDisplaySize().X * 0.12f, mpDataManager->GetDisplaySize().Y * 0.17f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 1], MIDDLE_FLAG);
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.77f,
			mpDataManager->GetDisplaySize().X * 0.1f, mpDataManager->GetDisplaySize().Y * 0.15f, 1.0f / 3.0f, 2.0f / 3.0f, 0.0f, 1.0f / 4.0f, mnResourceIDs[mnSelectNumber], MIDDLE_FLAG);

		// 名前
		fontData = FontData();
		fontData.fontSize = 60.0f;
		fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD;
		Master::mpResourceManager->SetFontData(&fontData);
		Master::mpResourceManager->DrawString("NAME : " + mpDataManager->GetPlayerData(mnSelectNumber).name,
			XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.2f, mpDataManager->GetDisplaySize().Y * 0.3f), D2D1_DRAW_TEXT_OPTIONS_NONE);

		// スコア
		Master::mpResourceManager->DrawString("SCORE : " + std::to_string(mpDataManager->GetPlayerData(mnSelectNumber).result.score),
			XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.2f, mpDataManager->GetDisplaySize().Y * 0.4f), D2D1_DRAW_TEXT_OPTIONS_NONE);

		// ダメージを受けた回数
		Master::mpResourceManager->DrawString("DAMAGE : " + std::to_string(mpDataManager->GetPlayerData(mnSelectNumber).result.damegeCount),
			XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.2f, mpDataManager->GetDisplaySize().Y * 0.5f), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}

	fontData = FontData();
	Master::mpResourceManager->SetFontData(&fontData);
}

/*選択決定時処理*/
void ResultUI::DecisionProcess()
{
	Master::mpSceneManager->SetNextScene(SCENE_NAME::RE_GAME);
}


/*--------------------------------------------------------------------------------------------------------------
* 【プレイヤーコントローラー設定用UI】
*/
/*コンストラクタ*/
PlayerControllerUI::PlayerControllerUI()
: UIBase(1, true)
, mbStartFlag(false)
, mpDataManager(nullptr)
, mnBlinkTime(0)
, mbEndFlag(false)
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
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/KeyBoard/2.png"));
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/KeyBoard/0.png"));
	mnResourceIDs.push_back(Master::mpResourceManager->AddResource(L"Resource/KeyBoard/1.png"));
}

/*UI終了*/
void PlayerControllerUI::UIFinalize()
{
	for (int i = 0; i < mnResourceIDs.size(); i++)
	{
		Master::mpResourceManager->SubResource(mnResourceIDs[i]);
	}
}

/*UI更新*/
void PlayerControllerUI::UIUpdate()
{
	if (mbStartFlag)
	{
		if ((mnBlinkTime + 40) < Master::mpTimeManager->GetFrame())
		{
			mnBlinkTime = Master::mpTimeManager->GetFrame() + 40;
		}

		if (mpKeyState->GetKeyUpAllController(CONTROLLER_KEY_TYPE::B) && mbEndFlag)
		{
			if (mnSelectNumber == 0)
			{
				mbStartFlag = false;
				DeleteUINumber();
			}
			mnSelectNumber = mnMaxSelectNumber + 1;
			DecisionProcess();
		}
		if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::B))
		{
			mbEndFlag = true;
		}

		if (mnSelectNumber >= mnMaxSelectNumber)
		{
			for (int i = 0; i < mnMaxSelectNumber; i++)
			{

				if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::A, mnSetPlayerKey[i]))
				{
					DecisionProcess();
				}
			}
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
}

/*最終描画*/
void PlayerControllerUI::LastDraw()
{
	if (mbStartFlag)
	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.5f,
			mpDataManager->GetDisplaySize().X * 1.0f, mpDataManager->GetDisplaySize().Y * 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[0], MIDDLE_FLAG);

		for (int i = 0; i < mnMaxSelectNumber; i++)
		{
			if (i < 3)
			{
				Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.2f + (mpDataManager->GetDisplaySize().X * (0.31f * i)), mpDataManager->GetDisplaySize().Y * 0.2f,
					mpDataManager->GetDisplaySize().X * 0.3f, mpDataManager->GetDisplaySize().Y * 0.3f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[1], MIDDLE_FLAG);
			}
			else
			{
				Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.2f + (mpDataManager->GetDisplaySize().X * (0.31f * (i - 3))), mpDataManager->GetDisplaySize().Y * 0.6f,
					mpDataManager->GetDisplaySize().X * 0.3f, mpDataManager->GetDisplaySize().Y * 0.3f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[1], MIDDLE_FLAG);
			}
		}

		if (mnSelectNumber >= mnMaxSelectNumber)
		{
			for (int i = 0; i < mnSelectNumber; i++)
			{
				if (mnBlinkTime < Master::mpTimeManager->GetFrame())
				{
					ControllerDraw(i, mnResourceIDs[3], mnResourceIDs[7], mnSetPlayerKey[i] == 0);
				}
				else
				{
					ControllerDraw(i, mnResourceIDs[5], mnResourceIDs[8], mnSetPlayerKey[i] == 0);
				}
			}
		}
		else
		{
			for (int i = 0; i < mnSelectNumber; i++)
			{
				ControllerDraw(i, mnResourceIDs[2], mnResourceIDs[6], mnSetPlayerKey[i] == 0);
			}

			if (mnBlinkTime < Master::mpTimeManager->GetFrame())
			{
				ControllerDraw(mnSelectNumber, mnResourceIDs[3]);
			}
			else
			{
				ControllerDraw(mnSelectNumber, mnResourceIDs[4]);
			}
		}
	}
}

/*プレイヤーキー設定開始*/
void PlayerControllerUI::SetControllerStart()
{
	mnSelectNumber = 0;
	mnMaxSelectNumber = (int)mpDataManager->GetPlayerData().size();
	mbStartFlag = true;
	mbEndFlag = false;

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

		mbStartFlag = false;
		DeleteUINumber();
	}
}

/*コントローラー描画*/
void PlayerControllerUI::ControllerDraw(int number, int resourceID, int keyBoardResourceID, bool keyBoardFlag)
{
	if (keyBoardFlag)
	{
		if (number < 3)
		{
			Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.2f + (mpDataManager->GetDisplaySize().X * (0.31f * number)), mpDataManager->GetDisplaySize().Y * 0.2f,
				mpDataManager->GetDisplaySize().X * 0.29f, mpDataManager->GetDisplaySize().Y * 0.29f, 0.0f, 1.0f, 0.0f, 1.0f, keyBoardResourceID, MIDDLE_FLAG);
		}
		else
		{
			Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.2f + (mpDataManager->GetDisplaySize().X * (0.31f * (number - 3))), mpDataManager->GetDisplaySize().Y * 0.6f,
				mpDataManager->GetDisplaySize().X * 0.29f, mpDataManager->GetDisplaySize().Y * 0.29f, 0.0f, 1.0f, 0.0f, 1.0f, keyBoardResourceID, MIDDLE_FLAG);
		}
	}
	else
	{
		if (number < 3)
		{
			Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.2f + (mpDataManager->GetDisplaySize().X * (0.31f * number)), mpDataManager->GetDisplaySize().Y * 0.2f,
				mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.55f, 0.0f, 1.0f, 0.0f, 1.0f, resourceID, MIDDLE_FLAG);
		}
		else
		{
			Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.2f + (mpDataManager->GetDisplaySize().X * (0.31f * (number - 3))), mpDataManager->GetDisplaySize().Y * 0.6f,
				mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.55f, 0.0f, 1.0f, 0.0f, 1.0f, resourceID, MIDDLE_FLAG);
		}
	}
}