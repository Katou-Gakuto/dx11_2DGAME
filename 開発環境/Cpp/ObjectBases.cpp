#include "../Header/Attacks.h"
#include "../Header/GameManager.h"
#include "../Header/KeyState.h"
#include "../Header/Macro.h"
#include "../Header/Master.h"
#include "../Header/ObjectBases.h"
#include "../Header/ObjectManager.h"
#include "../Header/ResourceManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TargetDatas.h"
#include "../Header/TimeManager.h"
#include "../Header/TemplateData.h"
#include "../Header/UIManager.h"


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【オブジェクトベース】
*/
unsigned int ObjectBase::mnSetIDMax = 0;
// コンストラクタ
ObjectBase::ObjectBase(OBJECT_TYPE objectType)
: mpNextObject(nullptr)
, mpPrevObject(nullptr)
, mpInheritClassNextObject(nullptr)
, mpInheritClassPrevObject(nullptr)
, mnTag(0)
, mbIsDeleteFlag(false)
, meObjectType(objectType)
{
	Master::mpGameManager->GetObjectManager()->Add(this, (int)objectType);

	mnID = mnSetIDMax += 1;

	meObjectScene = Master::mpSceneManager->GetNowScene();
}

// デストラクタ
ObjectBase::~ObjectBase()
{
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【キャラクターベース】
*/
// コンストラクタ
CharacterBase::CharacterBase(DrawData drawData, bool drawFlag, CharacterControllerBase* controller, int upNumber, int downNumber, int leftNumber, int rightNumber, int stopNumber, int attackTime, int attackIntervalTime, STATUS status, bool hpZeroDeleteFlag)
: ObjectBase(OBJECT_TYPE::CHARACTER_BASE)
, mstStatus(status)
, mstOldPosition(VECTOR_2D::Zero())
, mstMoveVec(VECTOR_2D::Zero())
, mnAngle(0)
, mnMoveFlags(0)
, mnStopTime(0)
, mpAttack(nullptr)
, mnAttackTime(attackTime)
, mnAttackIntervalTime(attackIntervalTime)
, mbDrawFlag(drawFlag)
, meState(STATE::STOP)
, meOldState(STATE::STOP)
, mstAnimeNumber(VECTOR_2D::Zero())
, mnPlusAnimeNumber(1)
, mnDownNumber(0)
, mnUpNumber(upNumber)
, mnLeftNumber(leftNumber)
, mnRightNumber(rightNumber)
, mnStopNumber(stopNumber)
, mnOneImageDrawTime(300)
, mnSetImageTime(0)
, mpChracterController(controller)
, mstDrawData(drawData)
, mbHpZeroDeleteFlag(hpZeroDeleteFlag)
{
}
// デストラクタ
CharacterBase::~CharacterBase()
{
}

// 初期化
void CharacterBase::Initilize()
{
	//mnResourceNumber = Master::mpResourceManager->AddResource(mwResourceFileName);

	CharacterInitilize();
}

// 終了
void CharacterBase::Finalize()
{
	if (mpAttack != nullptr)
	{
		mpAttack->SetDeleteFlag(true);
	}
	Master::mpResourceManager->SubResource(mstDrawData.resourceId);
	CharacterFinalize();
}

// 更新
void CharacterBase::Update()
{	
	if (mstStatus.HpCheck() && mbHpZeroDeleteFlag)
	{
		mpChracterController->SetDeleteFlag(true);
		this->SetDeleteFlag(true);
	}

	CharacterStartUpdate();

	MoveProcess();

	CharacterEndUpdate();
}

// 描画
void CharacterBase::Draw()
{
	if (mbDrawFlag)
	{
		if (!Master::mpTimeManager->GetStopFlag())
		{
			SetDrawData();
		}
		mstDrawData.Draw();
//		Master::mpResourceManager->DrawSprite(mstStatus.Position.X, mstStatus.Position.Y, mstStatus.Size.X, mstStatus.Size.Y, (float)mstAnimeNumber.IntX() * mstResourceSize[1].X, mstResourceSize[1].X, mstAnimeNumber.IntY() * mstResourceSize[1].Y, mstResourceSize[1].Y, mnResourceNumber, MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG);
	}

	CharacterDraw();
}

// 定型移動処理
void CharacterBase::TemplateMoveProcess()
{
	if (Master::mpTimeManager->GetStopFlag())
	{
		return;
	}

	mstOldPosition = mstStatus.Position;
	mstMoveVec = VECTOR_2D::Zero();

	if (mnMoveFlags != 0U)
	{
		if (mnStopTime > Master::mpTimeManager->GetGameTime())
		{

		}
		else if (mnMoveFlags & GetBitFlag(MOVE_FLAGS::ATTACK_MOVE))
		{
			if (mpAttack == nullptr)
			{
				switch (mstStatus.CharacterType)
				{
				case CHARACTER_TYPE::CLOSE_RENGE:
				{
					meState = STATE::ATTACK;

					VECTOR_2D plusPos = VECTOR_2D::Zero();
					VECTOR_2D attackSize = VECTOR_2D::Zero();
					wchar_t* fileName = NULL;
					switch (mnAngle)
					{
					case 0: // 下
						attackSize = VECTOR_2D::GetFloatVec(3.0f, 2.0f) * mstStatus.Size;
						plusPos.Y += mstStatus.Size.Y * 0.5f;
						fileName = (wchar_t*)L"Resource/BattleEffect/pipo-btleffect096a.png";
						break;

					case 1: // 左
						attackSize = VECTOR_2D::GetFloatVec(2.0f, 3.0f) * mstStatus.Size;
						plusPos.X -= mstStatus.Size.X * 0.5f;
						fileName = (wchar_t*)L"Resource/BattleEffect/pipo-btleffect090a.png";
						break;

					case 2: // 上
						attackSize = VECTOR_2D::GetFloatVec(2.0f, 3.0f) * mstStatus.Size;
						plusPos.Y -= mstStatus.Size.Y * 0.5f;
						fileName = (wchar_t*)L"Resource/BattleEffect/pipo-btleffect096.png";
						break;

					case 3: // 右
						attackSize = VECTOR_2D::GetFloatVec(2.0f, 3.0f) * mstStatus.Size;
						plusPos.X += mstStatus.Size.X * 0.5f;
						fileName = (wchar_t*)L"Resource/BattleEffect/pipo-btleffect090a.png";
						break;
					}

					COLLISION_TYPE setObjectTyoe = COLLISION_TYPE::NONE;
					if (mpChracterController->GetObjectTypeNumber() == (int)OBJECT_TYPE::CHARACTER_CONTROLLER_PLAYER)
					{
						setObjectTyoe = COLLISION_TYPE::PLAYER;
					}
					else if (mpChracterController->GetObjectTypeNumber() == (int)OBJECT_TYPE::CHARACTER_CONTROLLER_ENEMY)
					{
						setObjectTyoe = COLLISION_TYPE::ENEMY;
					}
					mnStopTime = mnAttackTime + mnAttackIntervalTime + Master::mpTimeManager->GetGameTime();
					mpAttack = new CloseRangeAttack(fileName, this, mnAttackTime, mstStatus.Position + plusPos, attackSize, setObjectTyoe, mstStatus.AttackPower);
					mpAttack->Initilize();
				}
				break;
				}
			}
		}
		else
		{

			if (mnMoveFlags & GetBitFlag(MOVE_FLAGS::UP_OR_DOWN_MOVE))
			{
				if (mnMoveFlags & GetBitFlag(MOVE_FLAGS::DOWN_MOVE))
				{
					mstMoveVec.Y += mstStatus.Speed;
				}
				else
				{
					mstMoveVec.Y -= mstStatus.Speed;
				}
			}

			if (mnMoveFlags & GetBitFlag(MOVE_FLAGS::LEFT_OR_RIGHT_MOVE))
			{
				if (mnMoveFlags & GetBitFlag(MOVE_FLAGS::RIGHT_MOVE))
				{
					mstMoveVec.X += mstStatus.Speed;
				}
				else
				{
					mstMoveVec.X -= mstStatus.Speed;
				}
			}
		}

		// 移動処理
		{
			if (mstMoveVec == VECTOR_2D::Zero())
			{
				meState = STATE::STOP;
			}
			else
			{
				meState = STATE::WALK;
				mstStatus.Position += mstMoveVec;
			}
		}

		mnMoveFlags = 0U;
	}
	else
	{
		if (mpAttack == nullptr)
		{
			meState = STATE::STOP;
		}
	}
}

// 定型描画前情報設定
void CharacterBase::TemplateSetDrawData()
{
	int setAnime = -1;
	if (mstMoveVec.X < 0.0f)
	{
		setAnime = mnLeftNumber;
		mnAngle = 1;
	}
	else if (mstMoveVec.X > 0.0f)
	{
		setAnime = mnRightNumber;
		mnAngle = 3;
	}
	else if (mstMoveVec.Y > 0.0f)
	{
		setAnime = mnDownNumber;
		mnAngle = 0;
	}
	else if (mstMoveVec.Y < 0.0f)
	{
		setAnime = mnUpNumber;
		mnAngle = 2;
	}

	mstDrawData.drawPos = mstStatus.Position;
	mstDrawData.DrawUpdate(setAnime);
	/*
	if (setAnime != -1)
	{
		mstDrawData.drawType = DRAW_TYPE::LOOP_X_AXIS_I_RETURN_DRAW;
		if (mstAnimeNumber.Y == setAnime)
		{
			/*
			if ((Master::mpTimeManager->GetGameTime() - mnSetImageTime) >= mnOneImageDrawTime)
			{
				mnSetImageTime = Master::mpTimeManager->GetGameTime();

				mstAnimeNumber.X += mnPlusAnimeNumber;
				if ((mstAnimeNumber.IntX() >= mstResourceSize[0].IntX()) || (mstAnimeNumber.X < 0))
				{
					if (mbReturnCallImageFlag)
					{
						mnPlusAnimeNumber *= -1;
						mstAnimeNumber.X += (mnPlusAnimeNumber * 2);
					}
					else
					{
						mstAnimeNumber.X = 0;
					}
				}
			}*//*
		}
		else
		{
			mnPlusAnimeNumber = 1;
			mstAnimeNumber.Y = (float)setAnime;
			mstAnimeNumber.X = (float)mnStopNumber;
			mnSetImageTime = Master::mpTimeManager->GetGameTime();
		}
	}
	else
	{
		mstAnimeNumber.X = (float)mnStopNumber;
		mnPlusAnimeNumber = 1;
	}*/
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【キャラクターコントローラーベース】
*/
// コンストラクタ
CharacterControllerBase::CharacterControllerBase(OBJECT_TYPE objectType)
: ObjectBase(objectType)
, mpCharacter(nullptr)
, meSetCharacterType(CHARACTER_TYPE::NONE)
, mbInitilizeFlag(false)
{
}
// デストラクタ
CharacterControllerBase::~CharacterControllerBase()
{
}

// 初期化
void CharacterControllerBase::Initilize()
{
	mbInitilizeFlag = true;
	CharacterControllerInitilize();
}

// 終了
void CharacterControllerBase::Finalize()
{
	CharacterControllerFinalize();
}

// 更新
void CharacterControllerBase::Update()
{
	if (mbInitilizeFlag)
	{
		CharacterControllerUpdate();
	}
}

// 描画
void CharacterControllerBase::Draw()
{
	if (mbInitilizeFlag)
	{
		CharacterControllerDraw();
	}
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【コリジョンベース】
*/
// コンストラクタ
CollisionBase::CollisionBase(VECTOR_2D position, VECTOR_2D size, const wchar_t* resourceFileName, VECTOR_2D LeftUpUV, VECTOR_2D RightDownUV)
: ObjectBase(OBJECT_TYPE::COLLISION_BASE)
, mstPosition(position)
, mstSize(size)
, mwResourceFileName((wchar_t*)resourceFileName)
, mnResourceNumber(-1)
, mbDrawFlag(true)
{
	mstUV[0] = LeftUpUV;
	mstUV[1] = RightDownUV;
}
// コンストラクタ
CollisionBase::CollisionBase(VECTOR_2D position, VECTOR_2D size)
: ObjectBase(OBJECT_TYPE::COLLISION_BASE)
, mstPosition(position)
, mstSize(size)
, mwResourceFileName(NULL)
, mnResourceNumber(-1)
, mbDrawFlag(false)
{
	mstUV[0] = VECTOR_2D::Zero();
	mstUV[1] = VECTOR_2D::Zero();
}
// デストラクタ
CollisionBase::~CollisionBase()
{
}

// 初期化
void CollisionBase::Initilize()
{
	if (mwResourceFileName != NULL)
	{
		mnResourceNumber = Master::mpResourceManager->AddResource(mwResourceFileName);
	}
	CollisionInitilize();
}

// 終了
void CollisionBase::Finalize()
{
	if (mnResourceNumber != -1)
	{
		Master::mpResourceManager->SubResource(mnResourceNumber);
	}
	CollisionFinalize();
}

// 更新
void CollisionBase::Update()
{
	CollisionUpdate();
}

// 描画
void CollisionBase::Draw()
{
	if (mnResourceNumber != -1)
	{
		Master::mpResourceManager->DrawSprite(mstPosition.X, mstPosition.Y, mstSize.X, mstSize.Y, mstUV[1].X, mstUV[0].X, mstUV[1].Y, mstUV[0].Y, mnResourceNumber, MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG);
	}
	CollisionDraw();
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【アタックベース】
*/
// コンストラクタ
AttackBase::AttackBase(DrawData drawData, CharacterBase* attackCharacter, int attackTime, VECTOR_2D attackPosition, VECTOR_2D attackSize, COLLISION_TYPE objectType, int attackPower)
: ObjectBase(OBJECT_TYPE::ATTACK_BASE)
, mstDrawData(drawData)
, mstAttackPosition(attackPosition)
, mstAttackSize(attackSize)
, mnAttackTime(attackTime + Master::mpTimeManager->GetGameTime())
, meObjectType(objectType)
, mstCollisionData(CollisionData::InitData())
, mnAttackPower(attackPower)
, mpAttackCharacter(attackCharacter)
{
	mpHitCharacters.clear();
}
// デストラクタ
AttackBase::~AttackBase()
{
}

// 初期化
void AttackBase::Initilize()
{
	mstDrawData.drawSize = mstAttackSize;
	mstCollisionData.ObjectType = meObjectType;
	AttackInitilize();
}

// 終了
void AttackBase::Finalize()
{
	Master::mpResourceManager->SubResource(mstDrawData.resourceId);
	AttackFinalize();
}

// 更新
void AttackBase::Update()
{
	if (Master::mpTimeManager->GetGameTime() > mnAttackTime)
	{
		mpAttackCharacter->ReSetAttack();
		SetDeleteFlag(true);
	}

	AttackUpdate();
}

// 描画
void AttackBase::Draw()
{
	AttackDraw();
}

// 定型攻撃処理
void AttackBase::TemplateAttackProcess()
{
	std::vector<CharacterBase*> attackObject;
	if (mstCollisionData.ObjectType == COLLISION_TYPE::PLAYER)
	{
		attackObject = Master::mpGameManager->GetTargetDatas()->GetEnemys();
	}
	else if (mstCollisionData.ObjectType == COLLISION_TYPE::ENEMY)
	{
		attackObject = Master::mpGameManager->GetTargetDatas()->GetPlayers();
	}

	for (int i = 0; i < attackObject.size(); i++)
	{
		bool checkFlag = true;
		for (int j = 0; j < mpHitCharacters.size(); j++)
		{
			if (attackObject[i]->GetID() == mpHitCharacters[j]->GetID())
			{
				checkFlag = false;
				break;
			}
		}

		if (checkFlag)
		{
			if (attackObject[i]->HitCheck(mstCollisionData).HitCount > 0)
			{
				mpHitCharacters.push_back(attackObject[i]);
				if (!attackObject[i]->GetStatus().HpCheck())
				{
					attackObject[i]->GetStatus().Damege(mnAttackPower);
					if (attackObject[i]->GetStatus().HpCheck())
					{
						mpAttackCharacter->GetStatus().PlusScore(5);
					}
				}
			}
		}
	}
}

// 定型描画処理
void AttackBase::TemplateDrawProcess()
{
	mstDrawData.drawPos = mstAttackPosition;
	mstDrawData.DrawUpdate(Master::mpTimeManager->GetStopFlag() ? -1 : 0);
	mstDrawData.Draw();
//	Master::mpResourceManager->DrawSprite(mstAttackPosition.X, mstAttackPosition.Y, mstAttackSize.X, mstAttackSize.Y, 0.0f, mstUVSize.X, 0.0f, mstUVSize.Y, mnResourceNumber, MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG);
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【UIベース】
*/
bool UIBase::mbDecisionFlag = false;
// コンストラクタ
UIBase::UIBase(int maxMenuSelect, bool keyboardFlag, bool timeStopFlag, bool decreaseFlag)
: ObjectBase(OBJECT_TYPE::UI_BASE)
, mpKeyState(nullptr)
, mpResourceManager(nullptr)
, mnSelectNumber(0)
, mnMaxSelectNumber(maxMenuSelect)
, mnChangeFrame(0)
, mnUINumber(0)
, mpTimeManager(nullptr)
, mbKeyBoardFlag(keyboardFlag)
{

	mbTimeStopFlag = timeStopFlag;

	if (mbTimeStopFlag)
	{
		mbDeleteDecreaseFlag = decreaseFlag;
	}
	else
	{
		mbDeleteDecreaseFlag = false;
	}
}

// デストラクタ
UIBase::~UIBase()
{
}

// 初期化
void UIBase::Initilize()
{
	if (mbTimeStopFlag)
	{
		SetUINumber();
	}

	mpKeyState = Master::mpKeyState;
	mpResourceManager = Master::mpResourceManager;
	mpTimeManager = Master::mpTimeManager;

	if (mbKeyBoardFlag)
	{
		mpKeyState->SetKeyBoardFlag(true);
	}

	UIInitilize();
}

// 終了
void UIBase::Finalize()
{
	if (mbDeleteDecreaseFlag) {
		DeleteUINumber();
	}

	if (mbKeyBoardFlag)
	{
		mpKeyState->SetKeyBoardFlag(false);
	}

	UIFinalize();
}

// 更新
void UIBase::Update()
{
	if (mnUINumber == Master::mpUIManager->GetNowUINumber()) {
		UIUpdate();
	}
}

// 最終更新
void UIBase::LastUpdate()
{
	if (mbDecisionFlag)
	{
		mbDecisionFlag = false;
	}
}

// 描画
void UIBase::Draw()
{
	UIDraw();
}

// UIナンバー設定
void UIBase::SetUINumber()
{
	mnUINumber = Master::mpUIManager->IncreaseUINumber(this);
}
// UIナンバー削除
void UIBase::DeleteUINumber()
{
	Master::mpUIManager->DecreaseUINumber();
}

/*-------------------------------------------------------
* 【入力キー種類別処理】
*/
// マウスが反応したら関数を実行させる
void UIBase::CheckMouse()
{
	if ((mpKeyState->GetMouseFlags() & 0x1ff) != 0)
	{
		MouseProcess();
	}
}

// キーボードが反応したら関数を実行させる
void UIBase::CheckKeyboard()
{
	if (((unsigned long long)mpKeyState->GetDownWordKeyFlags_Board() | (unsigned long long)mpKeyState->GetDownSpecialKeyFlags_Board() | (unsigned long long)mpKeyState->GetDownNumpadKeyFlags_Board() |
		(unsigned long long)mpKeyState->GetUpWordKeyFlags_Board() | (unsigned long long)mpKeyState->GetUpSpecialKeyFlags_Board() | (unsigned long long)mpKeyState->GetUpNumpadKeyFlags_Board()) != 0)
	{
		KeyboardProcess();
	}
}

// コントローラーが反応したら関数を実行させる
void UIBase::CheckController()
{
	if (mpKeyState->GetAllNowKeyFlags_Controller() != 0)
	{
		ControllerProcess();
	}
}

// キーボードかコントローラーが反応したら関数を実行させる
void UIBase::CheckKeyboard_Controller()
{
	if (((unsigned long long)mpKeyState->GetDownWordKeyFlags_Board() | (unsigned long long)mpKeyState->GetDownSpecialKeyFlags_Board() | (unsigned long long)mpKeyState->GetDownNumpadKeyFlags_Board() |
		(unsigned long long)mpKeyState->GetUpWordKeyFlags_Board() | (unsigned long long)mpKeyState->GetUpSpecialKeyFlags_Board() | (unsigned long long)mpKeyState->GetUpNumpadKeyFlags_Board() |
		(unsigned long long)mpKeyState->GetAllNowKeyFlags_Controller(false)) != 0)
	{
		Keyboard_ControllerProcess();
	}
}

/*-------------------------------------------------------
* 【テンプレート】
*/

// デフォルト選択処理
void UIBase::DefaultSelectProcess()
{
	DefaultDecrease();

	DefaultIncrease();

	DefaultDecision();
}

// デフォルト選択ナンバー減少処理
void UIBase::DefaultDecrease()
{
	if (CheckUp_Frame())
	{
		Decrease();
	}
}

// デフォルト選択ナンバー増加処理
void UIBase::DefaultIncrease()
{
	if (CheckDown_Frame())
	{
		Increase();
	}
}

/*選択ナンバー減少処理*/
void UIBase::Decrease()
{
	--mnSelectNumber;
	if (mnSelectNumber < 0)
	{
		mnSelectNumber = mnMaxSelectNumber - 1;
	}
}

/*選択ナンバー増加処理*/
void UIBase::Increase()
{
	++mnSelectNumber;
	if (mnSelectNumber >= mnMaxSelectNumber)
	{
		mnSelectNumber = 0;
	}
}

// デフォルト選択決定処理
void UIBase::DefaultDecision()
{
	if (CheckDecision())
	{
		DecisionProcess();
	}
}

// デフォルト終了確認処理
void UIBase::DefaultCloce()
{
	if ((mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::CTRL_LEFT_AND_RIGHT) && mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::Z)) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::B, false))
	{
		CloceProcess();
	}
}

// デフォルト終了処理
void UIBase::CloceProcess()
{
	SetDeleteFlag(true);
}

// 上が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckUp_Frame()
{
	if ((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::UP, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_UP, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_UP)) &&
		(CheckFrame(0) || (mnChangeFrame == mpTimeManager->GetFrame() + 15)))
	{
		mnChangeFrame = mpTimeManager->GetFrame() + 15;
		return true;
	}
	return false;
}

// 下が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckDown_Frame()
{
	if ((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::DOWN, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_DOWN, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_DOWN)) &&
		(CheckFrame(0) || (mnChangeFrame == mpTimeManager->GetFrame() + 15)))
	{
		mnChangeFrame = mpTimeManager->GetFrame() + 15;
		return true;
	}
	return false;
}

// 右が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckRight_Frame()
{
	if ((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::RIGHT, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_RIGHT, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_RIGHT)) &&
		(CheckFrame(0) || (mnChangeFrame == mpTimeManager->GetFrame() + 15)))
	{
		mnChangeFrame = mpTimeManager->GetFrame() + 15;
		return true;
	}
	return false;
}

// 左が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckLeft_Frame()
{
	if ((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_LEFT, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_LEFT)) &&
		(CheckFrame(0) || (mnChangeFrame == mpTimeManager->GetFrame() + 15)))
	{
		mnChangeFrame = mpTimeManager->GetFrame() + 15;
		return true;
	}
	return false;
}

// A/Enterが押されているなら「true」を返す
bool UIBase::CheckDecision()
{
	return (mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::A, false) || mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER) && !mbDecisionFlag);
}

// フレームが一定時間経っているかどうか
bool UIBase::CheckFrame(int frameNumber)
{
	switch (frameNumber)
	{
	case 0:
		return mnChangeFrame < mpTimeManager->GetFrame();
		break;
	}

	return false;
}
