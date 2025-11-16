#pragma once
#include <vector>

#include "TemplateData.h"

enum class SCENE_NAME;

class ObjectBase;

class ObjectManager
{
private:
    // 線形リストの先頭アドレス(オブジェクトべース)
    ObjectBase* mpObjectBase;

    // 線形リストの先頭アドレス(キャラクターべース)
    ObjectBase* mpCharacterBase;
    // 線形リストの先頭アドレス(キャラクターコントローラープレイヤー)
    ObjectBase* mpCharacterControllerPlayer;
    // 線形リストの先頭アドレス(キャラクターコントローラーエネミー)
    ObjectBase* mpCharacterControllerEnemy;

    // 線形リストの先頭アドレス(当たり判定べース)
    ObjectBase* mpCollisionBase;
    // 線形リストの先頭アドレス(攻撃べース)
    ObjectBase* mpAttackBase;
    // 線形リストの先頭アドレス(UIべース)
    ObjectBase* mpUIBase;

    // オブジェクト数が変更されたフラグ
    unsigned int mnObjectChangeFlags;
    // オブジェクト数が変更されたフラグ設定用
    unsigned int mnSetObjectChangeFlags;

public:
    /*コンストラクタ*/
    ObjectManager();
    /*デストラクタ*/
    ~ObjectManager();

    /*初期化*/
    void Initilize();
    /*終了*/
    void Finalize();
    /*更新*/
    void Update();
    /*最終更新*/
    void LastUpdate();
    /*描画*/
    void Draw();
    /*最終描画*/
    void LastDraw();

    /*リストにオブジェクトを追加する*/
    void Add(ObjectBase* object, int typeNumber);
    /*リストからオブジェクトを除外する*/
    void Delete(unsigned int id, int typeNumber);

    /*IDからオブジェクトを取得*/
    ObjectBase* FindByID(int id, bool deleteGetFlag = false);
    /*タグからオブジェクトを取得*/
    ObjectBase* FindByTag(int tag, int typeNumber = 0, bool deleteGetFlag = false);
    /*タグから複数オブジェクトを取得 */
    std::vector<ObjectBase*> FindsByTag(int tag, int typeNumber = 0, bool deleteGetFlag = false);
    /*指定されたタイプを全取得*/
    std::vector<ObjectBase*> FindsByType(int typeNumber, bool deleteGetFlag = false);

    /*指定したシーンで生成されたオブジェクトの削除フラグ有効にする*/
    void SetDeleteSceneObject(SCENE_NAME targetScene);

    /*オブジェクト全削除*/
    void DeleteAll();
    /*必要であればオブジェクト削除を行う*/
    void DeleteAllIfNeeded();

    /*タグにあったオブジェクトの削除フラグを有効化*/
    void DeleteSetTag(int tag);

    /*当たり判定確認*/
    CollisionData CheckObjectHit(CollisionData collisionData, int typeNumber);

    /*オブジェクトリスト変更フラグ取得*/
    unsigned int GetObjectChangeFlag() { return mnObjectChangeFlags; }

private:
    /*リストの先頭オブジェクトを取得*/
    ObjectBase* GetTypeObject(int typeNumber);
    /*リストの先頭オブジェクトを設定*/
    void SetTypeObject(int typeNumber, ObjectBase* setObject);
};