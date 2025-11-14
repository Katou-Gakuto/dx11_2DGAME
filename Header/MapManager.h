#pragma once
#include <vector>

#include "Macro.h"
#include "TemplateData.h"

#define MAP_CREATE_TYPE 1

class Camera;
class DataManager;
class ObjectManager;
class ResourceManager;

/*--------------------------------------------------------------------------------------------------------------
* マップタイプデータ
*/
/*-------------------------------------------------------
* 地面データタイプ
*/
enum class GROUND_TYPE
{
    DEFAULT = 0,// デフォルト
    PLAIN,// 平原
	FOREST,// 森林
    SAVANNA,// サバンナ
	WETLAND,// 湿地帯
	DESERT,// 砂漠
	SNOWFIELD,// 雪原
	VOLCANIC,// 火山地帯
};

/*------------------------------------------------------
* マップオブジェクトタイプ
*/
enum class MAP_OBJECT_TYPE
{
    DEFAULT = 0,// デフォルト
	ENEMY, // 敵キャラ
    FLOWER, // 花
    NONE,   // なし 
    TREE,   // 木
    ROCK,   // 岩
    BUSH,   // 茂み
    MOUNTAIN, // 山
    WATER_PUDDLE, // 水たまり
    ROAD,   // 道
};

/* コピー用
        case GROUND_TYPE::DEFAULT:
        case GROUND_TYPE::DESERT:
        case GROUND_TYPE::FOREST:
        case GROUND_TYPE::PLAIN:
        case GROUND_TYPE::SAVANNA:
        case GROUND_TYPE::SNOWFIELD:
        case GROUND_TYPE::VOLCANIC:
        case GROUND_TYPE::WETLAND:
* 
        case MAP_OBJECT_TYPE::DEFAULT:
        case MAP_OBJECT_TYPE::FLOWER:
        case MAP_OBJECT_TYPE::TREE:
        case MAP_OBJECT_TYPE::ROCK:
        case MAP_OBJECT_TYPE::BUSH:
        case MAP_OBJECT_TYPE::MOUNTAIN:
        case MAP_OBJECT_TYPE::WATER_PUDDLE:
        case MAP_OBJECT_TYPE::ROAD:
*/

/*--------------------------------------------------------------------------------------------------------------
* マップ変更データ
*/
struct MapChangeData
{
    static const unsigned int ARRAY_SIZE = MAP_HEIGHT_MAX > MAP_WIDTH_MAX ? MAP_HEIGHT_MAX : MAP_WIDTH_MAX;

    unsigned long groundData[MAP_HEIGHT_MAX > MAP_WIDTH_MAX ? MAP_HEIGHT_MAX : MAP_WIDTH_MAX];
    unsigned long mapObjectData[MAP_HEIGHT_MAX > MAP_WIDTH_MAX ? MAP_HEIGHT_MAX : MAP_WIDTH_MAX];

    // 設定ライン
    VECTOR_2D SetLine;

    

    /*初期化データ*/
    static MapChangeData InitData();

    /*一列分のデータ取得*/
    static MapChangeData GetOneLineData(int lineNumber, int lineType, VECTOR_2D pos);
    /*地面データタイプ取得*/
    static GROUND_TYPE GetGroundType(unsigned char number);
    /*地マップオブジェクトタイプ取得*/
    static MAP_OBJECT_TYPE GetMapObjectType(unsigned char number);
};

/*--------------------------------------------------------------------------------------------------------------
* マップデータ
*/
struct MapData
{
    MapData();

    // マップの右上座標(配列の左上)
    VECTOR_2D mapLeftUpPos;

    // マップのグラウンド
    unsigned long ground[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

    // マップ上のオブジェクト
    unsigned long mapObject[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

    // マップの使用リソースナンバー
    unsigned long mapResourceNumber[2][MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

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
    static MapData SetOneLine(const char XorYLine, MapData *src, MapChangeData changeData, VECTOR_2D mapPos, bool plusFlag = true);
    /*1タイル分の変更処理*/
	static void SetOneTile(MapData* src, VECTOR_2D mapPos, VECTOR_2D createPos, unsigned long groundNumber, unsigned long mapObjectNumber, std::vector<int> checkVecs);
    /*隣接タイルが違う種類が有効なフラグを返す*/
    static unsigned long GetDifferentFlag(unsigned long src[38][62], VECTOR_2D targetPos, unsigned long targettype);

    /*グラウンドもしくはマップオブジェクトのナンバーに合わせたリソースナンバーを返す*/
    static int GetGroundOrMapObject_ResourceNumber(int number, bool groundFlag = true);

    /*当たらない地点を返す(専用の構造体を返すようにする)(場所移す)(当たる奴と当たらない奴を判定する)*/
    VECTOR_2D GetNoHitPos(VECTOR_2D checkPos, VECTOR_2D srcPos, VECTOR_2D moveVec, VECTOR_2D srcSize);

    /*起動フラグ設定*/
    void SetStartupFlag(bool startupFlag) { mbStartupFlag = startupFlag; }
};