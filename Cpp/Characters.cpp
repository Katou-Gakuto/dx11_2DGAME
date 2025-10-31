#include <vector>

#include "../Header/Calculation.h"
#include "../Header/Characters.h"
#include "../Header/Collisions.h"
#include "../Header/GameManager.h"
#include "../Header/KeyState.h"
#include "../Header/Master.h"
#include "../Header/ObjectBases.h"
#include "../Header/ObjectManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TargetDatas.h"
#include "../Header/TemplateData.h"

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
PlayerManager::PlayerManager(std::vector<int> playerNumber, int playerHp)
: ObjectBase(OBJECT_TYPE::BASE)
, mnPlayerHP(playerHp)
{
	mpPlayerControllers.clear();
	mpPlayerControllers.reserve(playerNumber.size());
	for (int i = 0; i < playerNumber.size(); i++)
	{
		CharacterControllerBase* setController = new PlayerBase(playerNumber[i]);
		
		mpPlayerControllers.push_back(setController);
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
}

// 終了
void PlayerManager::Finalize()
{
}

// 更新
void PlayerManager::Update()
{
	for (int i = 0; i < mpPlayerControllers.size(); i++)
	{
		if (mpPlayerControllers[i]->GetCharacter()->GetStatus().HpCheck())
		{
			mnPlayerHP -= 1;

			if (mnPlayerHP > 0)
			{
				for (int i = 0; i < mpPlayerControllers.size(); i++)
				{
					mpPlayerControllers[i]->GetCharacter()->GetStatus().Recovery(1);
				}
			}
			else
			{
				for (int i = 0; i < mpPlayerControllers.size(); i++)
				{
					mpPlayerControllers[i]->SetDeleteFlag(true);
					mpPlayerControllers[i]->GetCharacter()->SetDeleteFlag(true);
				}
				mpPlayerControllers.clear();
				Master::mpSceneManager->SetNextScene(SCENE_NAME::RESULT);
			}

			return;
		}
	}
}

// 描画
void PlayerManager::Draw()
{
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【プレイヤーベース】
*/
// コンストラクタ
PlayerBase::PlayerBase(int playerNumber)
: CharacterControllerBase(OBJECT_TYPE::CHARACTER_CONTROLLER_PLAYER)
, mnPlayerNumber(playerNumber)
, mpKeyState(nullptr)
{
}

// デストラクタ
PlayerBase::~PlayerBase()
{
}

// キャラクターコントローラー初期化
void PlayerBase::CharacterControllerInitilize()
{
	mpCharacter = new CloseRangeCharacter(DrawData::GetDrawData(0, L"Resource/pipo-charachip001.png"), this, 3, 0, 1, 2, 1, STATUS::SetAllStatus(1, 1, 1, 1, 0.15f, VECTOR_2D::Zero(), VECTOR_2D::One(), CHARACTER_TYPE::CLOSE_RENGE), 450, 450, false);
	mpCharacter->Initilize();
	Master::mpGameManager->GetTargetDatas()->AddPlayer(mpCharacter);

	meSetCharacterType = CHARACTER_TYPE::CLOSE_RENGE;

	mpKeyState = Master::mpKeyState;
}

// キャラクターコントローラー終了
void PlayerBase::CharacterControllerFinalize()
{
	Master::mpGameManager->GetTargetDatas()->SubPlayer(mpCharacter);
}

// キャラクターコントローラー更新
void PlayerBase::CharacterControllerUpdate()
{
	TemplateKeyProcess();
}

// キャラクターコントローラー描画
void PlayerBase::CharacterControllerDraw()
{
}

// 定型キー行動
void PlayerBase::TemplateKeyProcess(int playerNumber)
{
	if (playerNumber == -1)
	{
		playerNumber = mnPlayerNumber;
	}

	//if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::UP, playerNumber))
	if (mpKeyState->GetMouse(MOUSE_TYPE::RIGHT_BUTTON))
	{
		mpCharacter->SetUpMove();
	}
	//if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::DOWN, playerNumber))
	if (mpKeyState->GetMouse(MOUSE_TYPE::LEFT_BUTTON))
	{
		mpCharacter->SetDownMove();
	}
	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::LEFT, playerNumber))
	{
		mpCharacter->SetLeftMove();
	}
	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::RIGHT, playerNumber))
	{
		mpCharacter->SetRightMove();
	}

	//if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::A, playerNumber))
	if (mpKeyState->GetMouse(MOUSE_TYPE::WHEEL_BUTTON))
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
	mpCharacter = new CloseRangeCharacter(DrawData::GetDrawData(0, L"Resource/pipo-charachip001.png"), this, 3, 0, 1, 2, 1, STATUS::SetAllStatus(1, 1, 1, 1, 0.05f, mstStartPosition, VECTOR_2D::One(), CHARACTER_TYPE::CLOSE_RENGE), 450, 1450);
	mpCharacter->Initilize();
	Master::mpGameManager->GetTargetDatas()->AddEnemy(mpCharacter);

	meSetCharacterType = CHARACTER_TYPE::CLOSE_RENGE;

	mfAttackRange = 1.0f;
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