#include <vector>

#include <DirectXMath.h>

#include "../Header/Calculation.h"
#include "../Header/Camera.h"
#include "../Header/Characters.h"
#include "../Header/Collisions.h"
#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/KeyState.h"
#include "../Header/Master.h"
#include "../Header/ObjectBases.h"
#include "../Header/ObjectManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TargetDatas.h"
#include "../Header/TemplateData.h"
#include "../Header/UIs.h"

using namespace DirectX;

class PlayerBase;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【キャラクターベース】
*/
// コンストラクタ
CloseRangeCharacter::CloseRangeCharacter(DrawData drawData, CharacterControllerBase* controller, int upNumber, int downNumber, int leftNumber, int rightNumber, int stopNumber, STATUS status, int attackTime, int attackIntervalTime, bool hpZeroDeleteFlag)
: CharacterBase(drawData, true, controller, upNumber, downNumber, leftNumber, rightNumber, stopNumber, attackTime, attackIntervalTime, status, hpZeroDeleteFlag)
{
}

// デストラクタ
CloseRangeCharacter::~CloseRangeCharacter()
{
}

// 当たり判定
CollisionData CloseRangeCharacter::CharacterCheck(CollisionData collisionData)
{
	switch (collisionData.CollisionType)
	{
	case COLLISION_TYPE::BOX:
		if (CollisionFunctions::HitBox(collisionData.Position + collisionData.NotHitPosMove, collisionData.Size, mstStatus.Position, mstStatus.Size))
		{
			collisionData.HitCount += 1;
			
			if (!CollisionFunctions::SideCheck(collisionData.OldPosition.X, collisionData.Size.X, mstStatus.Position.X, mstStatus.Size.X))
			{
				collisionData.NotHitPosMove.X += (collisionData.OldPosition.X > mstStatus.Position.X ? ((mstStatus.Position.X + (mstStatus.Size.X * 0.5f)) - (collisionData.Position.X - (collisionData.Size.X * 0.5f))) : ((mstStatus.Position.X - (mstStatus.Size.X * 0.5f)) - (collisionData.Position.X + (collisionData.Size.X * 0.5f))));
			}
			if (!CollisionFunctions::SideCheck(collisionData.OldPosition.Y, collisionData.Size.Y, mstStatus.Position.Y, mstStatus.Size.Y))
			{
				collisionData.NotHitPosMove.Y += (collisionData.OldPosition.Y > mstStatus.Position.Y ? ((mstStatus.Position.Y + (mstStatus.Size.Y * 0.5f)) - (collisionData.Position.Y - (collisionData.Size.Y * 0.5f))) : ((mstStatus.Position.Y - (mstStatus.Size.Y * 0.5f)) - (collisionData.Position.Y + (collisionData.Size.Y * 0.5f))));
			}
		}
		break;
	}

	return collisionData;
}

// 初期化
void CloseRangeCharacter::CharacterInitilize()
{
}

// 終了
void CloseRangeCharacter::CharacterFinalize()
{
}

// 更新開始
void CloseRangeCharacter::CharacterStartUpdate()
{
}
// 更新終了
void CloseRangeCharacter::CharacterEndUpdate()
{
	CollisionData srcCollisionData = CollisionData::InitData();
	srcCollisionData.Position = mstStatus.Position;
	srcCollisionData.OldPosition = mstOldPosition;
	srcCollisionData.Size = mstStatus.Size;
	srcCollisionData.CollisionType = COLLISION_TYPE::BOX;
	if ((OBJECT_TYPE)mpChracterController->GetObjectTypeNumber() == OBJECT_TYPE::CHARACTER_CONTROLLER_PLAYER)
	{
		srcCollisionData.ObjectType = COLLISION_TYPE::PLAYER;
	}
	else if ((OBJECT_TYPE)mpChracterController->GetObjectTypeNumber() == OBJECT_TYPE::CHARACTER_CONTROLLER_ENEMY)
	{
		srcCollisionData.ObjectType = COLLISION_TYPE::ENEMY;
	}

	srcCollisionData = Master::mpGameManager->GetObjectManager()->CheckObjectHit(srcCollisionData, (int)OBJECT_TYPE::COLLISION_BASE);
	srcCollisionData = Master::mpGameManager->GetObjectManager()->CheckObjectHit(srcCollisionData, (int)OBJECT_TYPE::CHARACTER_BASE);
	mstStatus.Position += srcCollisionData.NotHitPosMove;
}

// 描画
void CloseRangeCharacter::CharacterDraw()
{
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【プレイヤーマネージャー】
*/
// コンストラクタ
PlayerManager::PlayerManager(int playerHp)
: ObjectBase(OBJECT_TYPE::BASE)
, mnPlayerHP(playerHp)
, mnResourceID(-1)
, mbSetControllerFlag(false)
, mpSetPlayerControllerUI(nullptr)
{
	DataManager* dataManager = Master::mpDataManager;
	mpPlayerControllers.clear();
	mpPlayerControllers.reserve(dataManager->GetPlayerCount());
	for (int i = 0; i < dataManager->GetPlayerCount(); i++)
	{
		CharacterControllerBase* setController = new PlayerBase(i);
		
		mpPlayerControllers.push_back(setController);
		mnDamegeCount.push_back(0);
	}
}

// デストラクタ
PlayerManager::~PlayerManager()
{
}

// 初期化
void PlayerManager::Initilize()
{
	for (int i = 0; i < mpPlayerControllers.size(); i++)
	{
		mpPlayerControllers[i]->Initilize();
	}

	mnResourceID = Master::mpResourceManager->AddResource(L"Resource/Heart.png");

	mpSetPlayerControllerUI = new PlayerControllerUI();
	mpSetPlayerControllerUI->Initilize();
}

// 終了
void PlayerManager::Finalize()
{
	Master::mpResourceManager->SubResource(mnResourceID);
}

// 更新
void PlayerManager::Update()
{
	if (mbSetControllerFlag)
	{
		if (!mpSetPlayerControllerUI->GetSettingUpFlag())
		{
			for (int i = 0; i < Master::mpDataManager->GetPlayerCount(); i++)
			{
				if (!Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::EXISTENCE, Master::mpDataManager->GetPlayerKeyNumber(i)))
				{
					mpSetPlayerControllerUI->SetControllerStart();
					return;
				}
			}

			mbSetControllerFlag = false;
		}
	}
	else
	{
		for (int i = 0; i < mpPlayerControllers.size(); i++)
		{
			if (mpPlayerControllers[i]->GetCharacter()->GetStatus().HpCheck())
			{
				mnPlayerHP -= 1;
				++mnDamegeCount[i];

				if (mnPlayerHP > 0)
				{
					mpPlayerControllers[i]->GetCharacter()->GetStatus().Recovery(1);
				}
				else if (mnPlayerHP == 0)
				{
					std::vector<PlayerData> setPlayerData = Master::mpDataManager->GetPlayerData();

					for (int j = 0; j < mpPlayerControllers.size(); j++)
					{
						setPlayerData[j].result.score = mpPlayerControllers[j]->GetCharacter()->GetStatus().Score;
						setPlayerData[j].result.damegeCount = mnDamegeCount[j];
					}

					Master::mpDataManager->SetPlayerData(setPlayerData);

					ResultUI* result = new ResultUI();
					result->Initilize();
					return;
				}
			}

			if (!Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::EXISTENCE, Master::mpDataManager->GetPlayerKeyNumber(i)))
			{
				mbSetControllerFlag = true;
				mpSetPlayerControllerUI->SetControllerStart();
			}
		}
	}
}

// 描画
void PlayerManager::Draw()
{
}

// 最終描画
void PlayerManager::LastDraw()
{
	for (int i = 0; i < mnPlayerHP; i++)
	{
		Master::mpResourceManager->DrawSprite(Master::mpDataManager->GetDisplaySize().X * 0.05f + (Master::mpDataManager->GetDisplaySize().X * (i * 0.06f)), Master::mpDataManager->GetDisplaySize().Y * 0.05f,
			Master::mpDataManager->GetDisplaySize().X * 0.05f, Master::mpDataManager->GetDisplaySize().Y * 0.05f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceID, MIDDLE_FLAG);
	}
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【プレイヤーベース】
*/
// コンストラクタ
PlayerBase::PlayerBase(int playerNumber)
: CharacterControllerBase(OBJECT_TYPE::CHARACTER_CONTROLLER_PLAYER)
, mnPlayerNumber(playerNumber)
, mnKeyNumber(-1)
, msName("NULL")
, mpKeyState(nullptr)
, mnCharacterType(0)
, mnResourceID(-1)
{
}

// デストラクタ
PlayerBase::~PlayerBase()
{
}

// キャラクターコントローラー初期化
void PlayerBase::CharacterControllerInitilize()
{
	DataManager* dataManager = Master::mpDataManager;
	mnCharacterType = dataManager->GetPlayerData(mnPlayerNumber).characterType;
	mnKeyNumber = dataManager->GetPlayerKeyNumber(mnPlayerNumber);
	msName = dataManager->GetPlayerName(mnPlayerNumber);

	wchar_t* fileName = nullptr;
	switch (mnCharacterType)
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
	mpCharacter = new CloseRangeCharacter(DrawData::GetDrawData(0, (const wchar_t*)fileName), this, 3, 0, 1, 2, 1, STATUS::SetAllStatus(1, 1, 1, 1, 0.15f, VECTOR_2D::Zero(), VECTOR_2D::One(), CHARACTER_TYPE::CLOSE_RENGE), 450, 450, false);
	mpCharacter->Initilize();
	Master::mpGameManager->GetTargetDatas()->AddPlayer(mpCharacter);

	meSetCharacterType = CHARACTER_TYPE::CLOSE_RENGE;

	mpKeyState = Master::mpKeyState;

	mnResourceID = Master::mpResourceManager->AddResource(L"Resource/Back.png");
}

// キャラクターコントローラー終了
void PlayerBase::CharacterControllerFinalize()
{
	Master::mpGameManager->GetTargetDatas()->SubPlayer(mpCharacter);
}

// キャラクターコントローラー更新
void PlayerBase::CharacterControllerUpdate()
{
	if (Master::mpDataManager->GetPlayerKeyNumber(mnPlayerNumber) != mnKeyNumber)
	{
		mnKeyNumber = Master::mpDataManager->GetPlayerKeyNumber(mnPlayerNumber);
	}

	TemplateKeyProcess();
}

// キャラクターコントローラー描画
void PlayerBase::CharacterControllerDraw()
{
}

// 最終描画
void PlayerBase::LastDraw()
{
	if (Master::mpTimeManager->GetStopFlag())
	{
		return;
	}

	FontData fontData = FontData();
	fontData.fontSize = 20.0f;
	Master::mpResourceManager->SetFontData(&fontData);

	Master::mpResourceManager->DrawSprite(mpCharacter->GetStatus().Position.X, mpCharacter->GetStatus().Position.Y - 0.65f, (msName.size() + 2) * 20.0f * 0.01f * Master::mpGameManager->GetCamera()->GetCameraSize().X, 0.5f * Master::mpGameManager->GetCamera()->GetCameraSize().Y, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceID, MIDDLE_FLAG | CAMERA_VIEW_FLAG);
	Master::mpResourceManager->DrawString(msName, XMFLOAT2(mpCharacter->GetStatus().Position.X, mpCharacter->GetStatus().Position.Y - 0.7f), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG | CAMERA_VIEW_FLAG, fontData.fontSize);


	fontData = FontData();
	Master::mpResourceManager->SetFontData(&fontData);
}

// 定型キー行動
void PlayerBase::TemplateKeyProcess(int keyNumber)
{
	if (keyNumber == -1)
	{
		keyNumber = mnKeyNumber;
	}

	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::UP, keyNumber))
	{
		mpCharacter->SetUpMove();
	}
	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::DOWN, keyNumber))
	{
		mpCharacter->SetDownMove();
	}
	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::LEFT, keyNumber))
	{
		mpCharacter->SetLeftMove();
	}
	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::RIGHT, keyNumber))
	{
		mpCharacter->SetRightMove();
	}

	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::A, keyNumber))
	{
		mpCharacter->SetAttack();
	}
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【エネミーベース】
*/
// コンストラクタ
EnemyBase::EnemyBase(VECTOR_2D startPos)
: CharacterControllerBase(OBJECT_TYPE::CHARACTER_CONTROLLER_ENEMY)
, meEnemyMoveType(ENEMY_MOVE_TYPE::DEFAULT)
, mfAttackRange()
, mstStartPosition(startPos)
{
}

// デストラクタ
EnemyBase::~EnemyBase()
{
}

// キャラクターコントローラー初期化
void EnemyBase::CharacterControllerInitilize()
{
	int time = Master::mpTimeManager->GetGameTime();
	int level = (int)((float)(int)(Master::mpDataManager->GetGameStartTime() - Master::mpTimeManager->GetGameTime()) * 0.00001f);
	if (level < 0)
	{
		level = -level;
	}
	level += 1;

	mpCharacter = new CloseRangeCharacter(DrawData::GetDrawData(0, L"Resource/Enemy/0.png"), this, 3, 0, 1, 2, 1, STATUS::SetAllStatus(level, 1, 1, 1, 0.05f, mstStartPosition, VECTOR_2D::One(), CHARACTER_TYPE::CLOSE_RENGE), 450, 1450);
	mpCharacter->Initilize();
	Master::mpGameManager->GetTargetDatas()->AddEnemy(mpCharacter);

	meSetCharacterType = CHARACTER_TYPE::CLOSE_RENGE;

	mfAttackRange = 1.5f;
}

// キャラクターコントローラー終了
void EnemyBase::CharacterControllerFinalize()
{
	Master::mpGameManager->GetTargetDatas()->SubEnemy(mpCharacter);
}

// キャラクターコントローラー更新
void EnemyBase::CharacterControllerUpdate()
{
	TemplateMove();
}

// キャラクターコントローラー描画
void EnemyBase::CharacterControllerDraw()
{
}

// 定型行動
void EnemyBase::TemplateMove()
{
	switch (meEnemyMoveType)
	{
	case ENEMY_MOVE_TYPE::DEFAULT:
	{
		VECTOR_2D targetVec = Master::mpGameManager->GetTargetDatas()->GetNearPlayerVec(mpCharacter->GetStatus().Position);

		if (Calculation::ErrorEqualEqual(targetVec.X, 0.0f))
		{
		}
		else if (targetVec.X > 0.0f)
		{
			mpCharacter->SetRightMove();
		}
		else
		{
			mpCharacter->SetLeftMove();
		}

		if (Calculation::ErrorEqualEqual(targetVec.Y, 0.0f))
		{
		}
		else if (targetVec.Y > 0.0f)
		{
			mpCharacter->SetDownMove();
		}
		else
		{
			mpCharacter->SetUpMove();
		}

		if (targetVec.Abs().GetAddXY() <= mfAttackRange)
		{
			mpCharacter->SetAttack();
		}
	}
		break;
	}
}