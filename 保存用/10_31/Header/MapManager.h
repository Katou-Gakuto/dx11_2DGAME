#pragma once
#include <vector>

#include "Macro.h"
#include "TemplateData.h"

class Camera;
class ObjectManager;
class ResourceManager;

/*--------------------------------------------------------------------------------------------------------------
* マップ変更データ
*/
struct MapChangeData
{
    static const unsigned int ARRAY_SIZE = MAP_HEIGHT_MAX > MAP_WIDTH_MAX ? MAP_HEIGHT_MAX : MAP_WIDTH_MAX;

    int groundData[MAP_HEIGHT_MAX > MAP_WIDTH_MAX ? MAP_HEIGHT_MAX : MAP_WIDTH_MAX];
    int mapObjectData[MAP_HEIGHT_MAX > MAP_WIDTH_MAX ? MAP_HEIGHT_MAX : MAP_WIDTH_MAX];

    // 設定ライン
    VECTOR_2D SetLine;

    /*初期化データ*/
    static MapChangeData InitData();

    /*一列分のデータ取得*/
    static MapChangeData GetOneLineData(int lineNumber, int lineType);
};

/*--------------------------------------------------------------------------------------------------------------
* マップデータ
*/
struct MapData
{
    // マップの右上座標(配列の左上)
    VECTOR_2D mapLeftUpPos;

    // マップのグラウンド
    int ground[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

    // マップ上のオブジェクト
    int mapObject[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

    // マップの使用リソースナンバー
    int mapResourceNumber[2][MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

    // 初期化データ
    static MapData InitData();

    /*--------------------------------------------------------------------------------------------------------------
    * 【マップ座標】関連
    */
    /*範囲外なら範囲内にして返す*/
    static VECTOR_2D CheckRange(VECTOR_2D checkPos);
    /*行をずらす*/
    VECTOR_2D NumberChange(VECTOR_2D changeVolume, VECTOR_2D mapPos);
};

/*--------------------------------------------------------------------------------------------------------------
* マップマネジャー
*/
class MapManager
{
private:
    // カメラ
    Camera* mpCamera;

	// リソースマネージャー
	static ResourceManager* mpResourceManager;

    // オブジェクトマネージャー
    ObjectManager* mpObjectManager;

    // マップデータ
    MapData mstMapDatas;

    // マップの現在座標
    VECTOR_2D mstMapPosition;

    // 起動フラグ
    bool mbStartupFlag;

    // 初期化オブジェクト
    static std::vector<ObjectBase*> mpInitilizeObject;

public:
    /*コンストラクタ*/
	MapManager();
    /*デストラクタ*/
	~MapManager();


    /*初期化*/
    void Initilize();
    /*終了*/
    void Finalize();
    /*更新*/
    void Update();
    /*描画*/
    void Draw();

    /*1ライン変更処理*/
    static MapData SetOneLine(const char XorYLine, MapData *src, MapChangeData changeData, VECTOR_2D mapPos);

    /*グラウンドもしくはマップオブジェクトのナンバーに合わせたリソースナンバーを返す*/
    static int GetGroundOrMapObject_ResourceNumber(int number, bool groundFlag = true);

    /*当たらない地点を返す(専用の構造体を返すようにする)(場所移す)(当たる奴と当たらない奴を判定する)*/
    VECTOR_2D GetNoHitPos(VECTOR_2D checkPos, VECTOR_2D srcPos, VECTOR_2D moveVec, VECTOR_2D srcSize);

    /*起動フラグ設定*/
    void SetStartupFlag(bool startupFlag) { mbStartupFlag = startupFlag; }

private:
    /*四角範囲描画*/
    //void MapOneSquareDraw(float x, float y, float left, float right, float up, float down, int resourceId, unsigned int intFlag = 0U);
};