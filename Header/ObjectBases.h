#pragma once
#include <vector>

#include "TemplateData.h"

enum class SCENE_NAME;

class AttackBase;
class CharacterControllerBase;
class KeyState;
class ResourceManager;
class TimeManager;

/*----------------------------------------------------------------------------------------------------
* 【オブジェクトタイプ】
*/
enum class OBJECT_TYPE
{
    BASE = 0,
    CHARACTER_BASE,
    CHARACTER_CONTROLLER_PLAYER,
    CHARACTER_CONTROLLER_ENEMY,
    COLLISION_BASE,
    ATTACK_BASE,
    UI_BASE
};

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【オブジェクトベース】
*/
class ObjectBase
{
private:
    // 前オブジェクトへのポインタ
    ObjectBase* mpPrevObject;
    // 次オブジェクトへのポインタ
    ObjectBase* mpNextObject;

    // 継承したクラスと同タイプの前オブジェクトへのポインタ
    ObjectBase* mpInheritClassPrevObject;
    // 継承したクラスと同タイプの次オブジェクトへのポインタ
    ObjectBase* mpInheritClassNextObject;

    // 削除フラグ
    bool mbIsDeleteFlag;
    // 識別タグ
    int mnTag;
    // 個別ナンバー
    unsigned int mnID;

    // 設定用 の個別ナンバーの最大数(オブジェクトマネージャーで初期化)
    static unsigned int mnSetIDMax;

    // オブジェクトの種類
    OBJECT_TYPE meObjectType;

protected:
    // 生成されたシーン
    SCENE_NAME meObjectScene;

public:

    /*コンストラクタ*/
    ObjectBase(OBJECT_TYPE objectType);
    /*デストラクタ*/
    ~ObjectBase();

    /*初期化*/
    virtual void Initilize() = 0;
    /*終了*/
    virtual void Finalize() = 0;
    /*更新*/
    virtual void Update() = 0;
    /*描画*/
    virtual void Draw() = 0;
    /*最終描画*/
    virtual void LastDraw() {};

    /*前オブジェクトへのポインタ取得*/
    ObjectBase* GetPrevObject(bool allBaseFlag = true) { return allBaseFlag ? mpPrevObject : mpInheritClassPrevObject; }
    /*次オブジェクトへのポインタ取得*/
    ObjectBase* GetNextObject(bool allBaseFlag = true) { return allBaseFlag ? mpNextObject : mpInheritClassNextObject; }

    /*前オブジェクトのポインタを設定する*/
    void SetPrevObject(ObjectBase* object, bool allBaseFlag = true) { if (allBaseFlag) { mpPrevObject = object; } else { mpInheritClassPrevObject = object; } }
    /*次オブジェクトのポインタを設定する*/
    void SetNextObject(ObjectBase* object, bool allBaseFlag = true) { if (allBaseFlag) { mpNextObject = object; } else { mpInheritClassNextObject = object; } }

    /*削除フラグ設定*/
    void SetDeleteFlag(bool flag) { mbIsDeleteFlag = flag; }
    /*削除フラグ取得*/
    bool IsDeleteFlag() { return mbIsDeleteFlag; }

    /*タグ設定*/
    void SetTag(int tag) { mnTag = tag; }
    /*タグ取得*/
    int GetTag() { return mnTag; }

    /*個別ナンバー取得*/
    unsigned int GetID() { return mnID; }
    /*個別ナンバー設定用を設定*/
    static void Set_SetID(int number) { mnSetIDMax = number; }

    /*オブジェクト種類(ナンバー)取得*/
    int GetObjectTypeNumber() { return (int)meObjectType; }

    /*オブジェクトのシーンを取得*/
    SCENE_NAME GetObjectScene() { return meObjectScene; }
    /*オブジェクトのシーン設定*/
    void SetObjectScene(SCENE_NAME objectScene) { meObjectScene = objectScene; }

    /*------------------------------------------------------------
    * 【継承処理キャスト省略用】
    */
    /*当たり判定*/
    virtual CollisionData HitCheck(CollisionData collisionData) { return collisionData; };
};


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【キャラクターベース】関係
*/
/*--------------------------------------------------------------------------------------------------------------
* 【キャラクターベース用enum】
*/
/*行動フラグ*/
enum class MOVE_FLAGS
{
    /*上下移動*/
    UP_OR_DOWN_MOVE = 0,
    /*上移動*/
    UP_MOVE,
    /*下移動*/
    DOWN_MOVE,
    /*右左移動*/
    LEFT_OR_RIGHT_MOVE,
    /*左移動*/
    LEFT_MOVE,
    /*右移動*/
    RIGHT_MOVE,

    /*攻撃*/
    ATTACK_MOVE,
};
/*状態*/
enum class STATE
{
    /*立ち止まる*/
    STOP = 0,
    /*歩く*/
    WALK,
    /*攻撃*/
    ATTACK
};
/*--------------------------------------------------------------------------------------------------------------
* 【キャラクターベースクラス】
*/
class CharacterBase : public ObjectBase
{
protected:
    // 1つ前の座標
    VECTOR_2D mstOldPosition;

    // 移動量
    VECTOR_2D mstMoveVec;

    // 方向
    int mnAngle;

    // ステータス
    STATUS mstStatus;

    // HP0の場合削除するフラグ
    bool mbHpZeroDeleteFlag;

    // 移動フラグ
    unsigned int mnMoveFlags;

    // 移動停止時間
    int mnStopTime;

    // 描画情報
    DrawData mstDrawData;

    // 再生中アニメナンバー
    VECTOR_2D mstAnimeNumber;

    // 再生用(画像の描画変更時に使う)
    int mnPlusAnimeNumber;
    // 1枚の画像の描画時間
    int mnOneImageDrawTime;
    // 画像を設定した時間
    int mnSetImageTime;
    /*------------------------------------------------------------
    * アニメナンバーズ(方向)
    */
    // 上
    int mnUpNumber;
    // 下
    int mnDownNumber;
    // 左
    int mnLeftNumber;
    // 右
    int mnRightNumber;
    // 立ち止まり
    int mnStopNumber;
    /*------------------------------------------------------------*/


    // 攻撃オブジェクトデータ保存用
    AttackBase* mpAttack;

    // 攻撃時間
    int mnAttackTime;
    // 攻撃インターバル時間
    int mnAttackIntervalTime;

    // 描画フラグ
    bool mbDrawFlag;

    // 状態
    STATE meState;
    // ひとつ前の状態
    STATE meOldState;

    // キャラクターコントローラー
    CharacterControllerBase* mpChracterController;

public:
    /*コンストラクタ*/
    CharacterBase(DrawData drawData, bool drawFlag, CharacterControllerBase* controller, int upNumber, int downNumber, int leftNumber, int rightNumber, int stopNumber, int attackTime, int attackIntervalTime, STATUS status, bool hpZeroDeleteFlag);
    /*デストラクタ*/
    ~CharacterBase();

    /*初期化*/
    void Initilize() override final;
    /*終了*/
    void Finalize() override final;
    /*更新*/
    void Update() override final;
    /*描画*/
    void Draw() override final;

    /*当たり判定*/
    CollisionData HitCheck(CollisionData collisionData) override { return CharacterCheck(collisionData); }

public:
    /*--------------------------------------------------------------------------------------------------------------
    * 【独自処理】
    */
    /*上移動設定*/
    void SetUpMove() { mnMoveFlags ^= (GetBitFlag(MOVE_FLAGS::UP_MOVE) + GetBitFlag(MOVE_FLAGS::UP_OR_DOWN_MOVE)); }
    /*下移動設定*/
    void SetDownMove() { mnMoveFlags ^= (GetBitFlag(MOVE_FLAGS::DOWN_MOVE) + GetBitFlag(MOVE_FLAGS::UP_OR_DOWN_MOVE)); }

    /*左移動設定*/
    void SetLeftMove() { mnMoveFlags ^= (GetBitFlag(MOVE_FLAGS::LEFT_MOVE) + GetBitFlag(MOVE_FLAGS::LEFT_OR_RIGHT_MOVE)); }
    /*右移動設定*/
    void SetRightMove() { mnMoveFlags ^= (GetBitFlag(MOVE_FLAGS::RIGHT_MOVE) + GetBitFlag(MOVE_FLAGS::LEFT_OR_RIGHT_MOVE)); }

    /*攻撃設定*/
    void SetAttack() { mnMoveFlags ^= GetBitFlag(MOVE_FLAGS::ATTACK_MOVE); }

    /*当たり判定用(継承用)*/
    virtual CollisionData CharacterCheck(CollisionData collisionData) = 0;

    /*攻撃リセット*/
    virtual void ReSetAttack() { mpAttack = nullptr; }

protected:
    /*ビットフラグナンバー取得(フラグ調べ用)*/
    unsigned int GetBitFlag(MOVE_FLAGS moveType) { return 1U << (int)moveType; }

    /*キャラクター初期化*/
    virtual void CharacterInitilize() = 0;
    /*キャラクター終了*/
    virtual void CharacterFinalize() = 0;

    /*キャラクター更新開始*/
    virtual void CharacterStartUpdate() = 0;
    /*キャラクター更新終了*/
    virtual void CharacterEndUpdate() {}

    /*キャラクター描画*/
    virtual void CharacterDraw() = 0;

    /*移動処理*/
    virtual void MoveProcess() { TemplateMoveProcess(); }

    /*定型移動処理*/
    void TemplateMoveProcess();

    /*描画前情報設定*/
    virtual void SetDrawData() { TemplateSetDrawData(); };
    /*定型描画前情報設定*/
    void TemplateSetDrawData();
    
public:
    /*--------------------------------------------------------------------------------------------------------------
    * 【取得・設定】
    */
    /*ステータス取得*/
    STATUS &GetStatus() { return mstStatus; }

    CharacterControllerBase* GetCharacterController() { return mpChracterController; }
};


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【キャラクターコントローラーベース】
*/
class CharacterControllerBase : public ObjectBase
{
private:
    bool mbInitilizeFlag;

protected:
    // キャラクター
    CharacterBase* mpCharacter;
    
    // 設定用キャラクタータイプ
    CHARACTER_TYPE meSetCharacterType;

public:
    /*コンストラクタ*/
    CharacterControllerBase(OBJECT_TYPE objectType);
    /*デストラクタ*/
    ~CharacterControllerBase();

    /*初期化*/
    void Initilize() override final;
    /*終了*/
    void Finalize() override final;
    /*更新*/
    void Update() override final;
    /*描画*/
    void Draw() override final;

public:
    /*--------------------------------------------------------------------------------------------------------------
    * 【独自処理】
    */
    /*キャラクター取得*/
    CharacterBase* GetCharacter() { return mpCharacter; }
protected:
    /*キャラクターコントローラー初期化*/
    virtual void CharacterControllerInitilize() = 0;
    /*キャラクターコントローラー終了*/
    virtual void CharacterControllerFinalize() = 0;
    /*キャラクターコントローラー更新*/
    virtual void CharacterControllerUpdate() = 0;
    /*キャラクターコントローラー描画*/
    virtual void CharacterControllerDraw() = 0;
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【コリジョンベース】
*/
class CollisionBase : public ObjectBase
{
protected:
    // 座標
    VECTOR_2D mstPosition;
    // 大きさ
    VECTOR_2D mstSize;

    // リソースファイル名
    wchar_t* mwResourceFileName;
    // リソースナンバー
    int mnResourceNumber;
    // 描画UV値
    VECTOR_2D mstUV[2];
    // 描画フラグ
    bool mbDrawFlag;
public:
    /*コンストラクタ*/
    CollisionBase(VECTOR_2D position, VECTOR_2D size, const wchar_t* resourceFileName, VECTOR_2D LeftUpUV, VECTOR_2D RightDownUV);
    /*コンストラクタ*/
    CollisionBase(VECTOR_2D position, VECTOR_2D size);
    /*デストラクタ*/
    ~CollisionBase();

    /*初期化*/
    void Initilize() override final;
    /*終了*/
    void Finalize() override final;
    /*更新*/
    void Update() override final;
    /*描画*/
    void Draw() override final;

    /*当たり判定用*/
    CollisionData HitCheck(CollisionData collisionData) override { return CollisionCheck(collisionData); }

public:
    /*--------------------------------------------------------------------------------------------------------------
    * 【独自処理】
    */
    /*当たり判定(継承用)*/
    virtual CollisionData CollisionCheck(CollisionData collisionData) = 0;

protected:
    /*コリジョン初期化*/
    virtual void CollisionInitilize() = 0;
    /*コリジョン終了*/
    virtual void CollisionFinalize() = 0;
    /*コリジョン更新*/
    virtual void CollisionUpdate() = 0;
    /*コリジョン描画*/
    virtual void CollisionDraw() = 0;
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【アタックベース】
*/
class AttackBase : public ObjectBase
{
protected:
    // 描画情報
    DrawData mstDrawData;
    // 攻撃ポジション
    VECTOR_2D mstAttackPosition;
    // 攻撃サイズ
    VECTOR_2D mstAttackSize;
    // 攻撃時間
    int mnAttackTime;

    // オブジェクト種類
    COLLISION_TYPE meObjectType;

    // 攻撃済みキャラクター
    std::vector<CharacterBase*> mpHitCharacters;

    // 攻撃力
    int mnAttackPower;

    // 当たり判定データ
    CollisionData mstCollisionData;

    // 攻撃キャラクター
    CharacterBase* mpAttackCharacter;

public:
    /*コンストラクタ*/
    AttackBase(DrawData drawData, CharacterBase* attackCharacter, int attackTime, VECTOR_2D attackPosition, VECTOR_2D attackSize, COLLISION_TYPE objectType, int attackPower);
    /*デストラクタ*/
    ~AttackBase();

    /*初期化*/
    void Initilize() override final;
    /*終了*/
    void Finalize() override final;
    /*更新*/
    void Update() override final;
    /*描画*/
    void Draw() override final;

public:
    /*--------------------------------------------------------------------------------------------------------------
    * 【独自処理】
    */

protected:
    /*アタック初期化*/
    virtual void AttackInitilize() = 0;
    /*アタック終了*/
    virtual void AttackFinalize() = 0;
    /*アタック更新*/
    virtual void AttackUpdate() = 0;
    /*アタック描画*/
    virtual void AttackDraw() = 0;

    /*定型攻撃処理*/
    void TemplateAttackProcess();

    /*定型描画処理*/
    void TemplateDrawProcess();
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【UIベース】
*/
class UIBase : public ObjectBase
{
private:
    // 自分のUIナンバー
    int mnUINumber;

    // 時間停止フラグ
    bool mbTimeStopFlag;

    // 削除時減少させるフラグ
    bool mbDeleteDecreaseFlag;

    // キーボード使用フラグ
    bool mbKeyBoardFlag;

protected:
    // キー状態
    KeyState* mpKeyState;

    // リソースマネージャー
    ResourceManager* mpResourceManager;

    // タイムマネジャー
    TimeManager* mpTimeManager;

    // 選択ナンバー
    int mnSelectNumber;
    
    // 最大選択ナンバー
    int mnMaxSelectNumber;

    // 選択変更したフレーム数
    int mnChangeFrame;


public:
    /*コンストラクタ*/
    UIBase(int maxMenuSelect, bool keyboardFlag = false, bool timeStopFlag = false, bool decreaseFlag = true);
    /*デストラクタ*/
    ~UIBase();

    /*初期化*/
    void Initilize() override final;
    /*終了*/
    void Finalize() override final;
    /*更新*/
    void Update() override final;
    /*描画*/
    void Draw() override final;

    /*--------------------------------------------------------------------------------------------------------------
    * 【独自処理】
    */
protected:
    /*UI初期化*/
    virtual void UIInitilize() = 0;
    /*UI終了*/
    virtual void UIFinalize() = 0;
    /*UI更新*/
    virtual void UIUpdate() = 0;
    /*UI描画*/
    virtual void UIDraw() = 0;

    /*UIナンバー設定*/
    void SetUINumber();
    /*UIナンバー削除*/
    void DeleteUINumber();

    /*-------------------------------------------------------
    * 【入力キー種類別処理】
    */
    /*マウスが反応したら関数を実行させる*/
    void CheckMouse();
    /*マウスが反応した時に実行する*/
    virtual void MouseProcess() {}

    /*キーボードが反応したら関数を実行させる*/
    void CheckKeyboard();
    /*キーボードが反応した時に実行する*/
    virtual void KeyboardProcess() {}
    
    /*コントローラーが反応したら関数を実行させる*/
    void CheckController();
    /*コントローラーが反応した時に実行する*/
    virtual void ControllerProcess() {}

    /*キーボードかコントローラーが反応したら関数を実行させる*/
    void CheckKeyboard_Controller();
    /*キーボードかコントローラーが反応した時に実行する*/
    virtual void Keyboard_ControllerProcess() {}

    /*-------------------------------------------------------
    * 【テンプレート】
    */

    /*デフォルト選択処理*/
    void DefaultSelectProcess();
    /*デフォルト選択ナンバー減少処理*/
    void DefaultDecrease();
    /*デフォルト選択ナンバー増加処理*/
    void DefaultIncrease();

    /*選択ナンバー減少処理*/
    void Decrease();
    /*選択ナンバー増加処理*/
    void Increase();


    /*デフォルト選択決定処理*/
    void DefaultDecision();
    /*選択決定時処理*/
    virtual void DecisionProcess() = 0;

    /*デフォルト終了確認処理*/
    void DefaultCloce();
    /*デフォルト終了処理*/
    virtual void CloceProcess();

    /*上が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す*/
    bool CheckUp_Frame();
    /*下が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す*/
    bool CheckDown_Frame();
    /*右が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す*/
    bool CheckRight_Frame();
    /*左が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す*/
    bool CheckLeft_Frame();

    /*A/Enterが押されているなら「true」を返す*/
    bool CheckDecision();

    /*フレームが一定時間経っているかどうか*/
    bool CheckFrame(int frameNumber);
};