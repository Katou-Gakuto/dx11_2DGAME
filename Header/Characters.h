#pragma once
#include <vector>

#include "ObjectBases.h"
#include "TemplateData.h"

class KeyState;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【近距離キャラクター】
*/
class CloseRangeCharacter : public CharacterBase
{
public:
	/*コンストラクタ*/
	CloseRangeCharacter(DrawData drawData, CharacterControllerBase* controller, int upNumber, int downNumber, int leftNumber, int rightNumber, int stopNumber, STATUS status, int attackTime, int attackIntervalTime, bool hpZeroDeleteFlag = true);
	/*デストラクタ*/
	~CloseRangeCharacter();

	/*当たり判定*/
	virtual CollisionData CharacterCheck(CollisionData collisionData) override;

protected:
	/*キャラクター初期化*/
	void CharacterInitilize() override;
	/*キャラクター終了*/
	void CharacterFinalize() override;
	/*キャラクター更新開始*/
	void CharacterStartUpdate() override;
	/*キャラクター更新終了*/
	void CharacterEndUpdate() override;
	/*キャラクター描画*/
	void CharacterDraw() override;
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【プレイヤー】関連
*/
/*--------------------------------------------------------------------------------------------------------------
* 【プレイヤーマネージャー】
*/
class PlayerManager : public ObjectBase
{
private:
	// プレイヤーコントローラー
	std::vector<CharacterControllerBase*> mpPlayerControllers;

	// プレイヤーHP
	int mnPlayerHP;

	// リソースID
	int mnResourceID;

public:
	/*コンストラクタ*/
	PlayerManager(int playerHp);
	/*デストラクタ*/
	~PlayerManager();

	/*初期化*/
	void Initilize() override final;
	/*終了*/
	void Finalize() override final;
	/*更新*/
	void Update() override final;
	/*描画*/
	void Draw() override final;
};
/*--------------------------------------------------------------------------------------------------------------
* 【プレイヤーコントローラー】
*/
class PlayerBase : public CharacterControllerBase
{
private:
	// プレイヤーナンバー
	int mnPlayerNumber;

	// キーナンバー
	int mnKeyNumber;

	// プレイヤーネーム
	std::string msName;

	// リソースID
	int mnResourceID;

protected:
	// キー状態
	KeyState* mpKeyState;

	int mnCharacterType;

public:
	/*コンストラクタ*/
	PlayerBase(int playerNumber);
	/*デストラクタ*/
	~PlayerBase();

protected:
	/*キャラクターコントローラー初期化*/
	virtual void CharacterControllerInitilize();
	/*キャラクターコントローラー終了*/
	virtual void CharacterControllerFinalize();
	/*キャラクターコントローラー更新*/
	virtual void CharacterControllerUpdate();
	/*キャラクターコントローラー描画*/
	virtual void CharacterControllerDraw();

	/*最終描画*/
	void LastDraw() override;

	/*定型キー行動*/
	void TemplateKeyProcess(int keyNumber = -1);
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【エネミー】関連
*/
enum class ENEMY_MOVE_TYPE
{
	DEFAULT = 0,
};

class EnemyBase : public CharacterControllerBase
{
protected:
	// エネミー挙動種類
	ENEMY_MOVE_TYPE meEnemyMoveType;

	// 攻撃範囲
	float mfAttackRange;

	// 開始ポジション
	VECTOR_2D mstStartPosition;

public:
	EnemyBase(VECTOR_2D startPos);
	~EnemyBase();

protected:
	/*キャラクターコントローラー初期化*/
	virtual void CharacterControllerInitilize();
	/*キャラクターコントローラー終了*/
	virtual void CharacterControllerFinalize();
	/*キャラクターコントローラー更新*/
	virtual void CharacterControllerUpdate();
	/*キャラクターコントローラー描画*/
	virtual void CharacterControllerDraw();

	/*定型行動*/
	void TemplateMove();
};