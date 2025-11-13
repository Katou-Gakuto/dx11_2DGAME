#include <vector>
#include <string.h>

#include "../Header/Camera.h"
#include "../Header/Characters.h"
#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/Macro.h"
#include "../Header/MapManager.h"
#include "../Header/Master.h"
#include "../Header/ObjectBases.h"
#include "../Header/ObjectManager.h"
#include "../Header/ResourceManager.h"
#include "../Header/TemplateData.h"


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【マップ変更データ】構造体
*/
// 初期化データ
MapChangeData MapChangeData::InitData()
{
    MapChangeData initDat;
    memset(initDat.groundData, 0, sizeof(initDat.groundData));//sizeof(int) * ARRAY_SIZE);
    memset(initDat.mapObjectData, 0, sizeof(initDat.mapObjectData));//sizeof(int) * ARRAY_SIZE);
    initDat.SetLine = VECTOR_2D::Zero();
    return initDat;
}

/*一列分のデータ取得*/
MapChangeData MapChangeData::GetOneLineData(int lineNumber, int lineType = 0)
{
    MapChangeData oneLineData = MapChangeData::InitData();

    switch (lineType)
    {
    case -1:
    {
        const int setLine[2][ARRAY_SIZE] =
        {
            {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},

            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };

        memcpy(oneLineData.groundData, setLine[0], sizeof(oneLineData.groundData));//sizeof(int) * ARRAY_SIZE);
        memcpy(oneLineData.mapObjectData, setLine[1], sizeof(oneLineData.mapObjectData));//sizeof(int) * ARRAY_SIZE);
    }
    break;

    case 0:
    {
        const int setLine[2][ARRAY_SIZE] =
        {
            {3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},

            {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}
        };

        memcpy(oneLineData.groundData, setLine[0], sizeof(oneLineData.groundData));//sizeof(int) * ARRAY_SIZE);
        memcpy(oneLineData.mapObjectData, setLine[1], sizeof(oneLineData.mapObjectData));//sizeof(int) * ARRAY_SIZE);
    }
    break;

    default:
        break;
    }

    oneLineData.SetLine = (float)lineNumber;
    {
        int setLine[2][ARRAY_SIZE] =
        {
            {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},

            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };

        memcpy(oneLineData.groundData, setLine[0], sizeof(oneLineData.groundData));//sizeof(int) * ARRAY_SIZE);
        memcpy(oneLineData.mapObjectData, setLine[1], sizeof(oneLineData.mapObjectData));//sizeof(int) * ARRAY_SIZE);
    }
    return oneLineData;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【マップデータ】構造体
*/
// 初期化データ(const変数を利用して返す)
MapData MapData::InitData()
{
    MapData initData;
    memset(initData.ground, -1, sizeof(initData.ground));//sizeof(int) * MAP_HEIGHT_MAX * MAP_WIDTH_MAX);
    memset(initData.mapObject, -1, sizeof(initData.mapObject));//sizeof(int) * MAP_HEIGHT_MAX * MAP_WIDTH_MAX);
    memset(initData.mapResourceNumber, -1, sizeof(initData.mapResourceNumber));//sizeof(int) * 2 * MAP_HEIGHT_MAX * MAP_WIDTH_MAX);
    initData.mapLeftUpPos = 0;
    return initData;
}

/*--------------------------------------------------------------------------------------------------------------
* 【マップ座標】関連
*/
// 範囲外なら範囲内にして返す
VECTOR_2D MapData::CheckRange(VECTOR_2D checkPos)
{
    VECTOR_2D result = checkPos.SetInt2D();

    if (result.IntY() >= MAP_HEIGHT_MAX)
    {
        result.Y -= MAP_HEIGHT_MAX * (result.IntY() / MAP_HEIGHT_MAX);
    }
    else if (result.IntY() < 0)
    {
        result.Y += MAP_HEIGHT_MAX * (1 + ((result.IntY() + 1) / -MAP_HEIGHT_MAX));
    }
   
    if (result.IntX() >= MAP_WIDTH_MAX)
    {
        result.X -= MAP_WIDTH_MAX * (result.IntX() / MAP_WIDTH_MAX);
    }
    else if (result.IntX() < 0)
    {
        result.X += MAP_WIDTH_MAX * (1 + ((result.IntX() + 1) / -MAP_WIDTH_MAX));
    }

    return result;
}

// 行をプラス方向にずらす
VECTOR_2D MapData::NumberChange(VECTOR_2D changeVolume, VECTOR_2D mapPos)
{
    VECTOR_2D moveNumber = VECTOR_2D::Zero();

    if (changeVolume.Y > 0.0f)
    {
        for (int y = 0; y < changeVolume.IntY(); y++)
        {
            MapManager::SetOneLine('Y', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntY() + y, Master::mpDataManager->GetBitMapData().GetMapPixel(false).blue), mapPos);
            moveNumber.Y += 1.0f;
        }
    }
    else if (changeVolume.Y < 0.0f)
    {
        for (int y = -1; y > changeVolume.IntY() - 1; y--)
        {
            MapManager::SetOneLine('Y', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntY() + y, Master::mpDataManager->GetBitMapData().GetMapPixel(false).blue), mapPos);
            moveNumber.Y -= 1.0f;
        }
    }

    if (changeVolume.X > 0.0f)
    {
        for (int x = 0; x < changeVolume.IntX(); x++)
        {
            MapManager::SetOneLine('X', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntX() + x, Master::mpDataManager->GetBitMapData().GetMapPixel(true).blue), mapPos);
            moveNumber.X += 1.0f;
        }
    }
    else if (changeVolume.X < 0.0f)
    {
        for (int x = -1; x > changeVolume.IntX() - 1; x--)
        {
            MapManager::SetOneLine('X', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntX() + x, Master::mpDataManager->GetBitMapData().GetMapPixel(true).blue), mapPos);
            moveNumber.X -= 1.0f;
        }
    }

    this->mapLeftUpPos = MapData::CheckRange(this->mapLeftUpPos.SetInt2D() + changeVolume.SetInt2D());

    return moveNumber;
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【マップマネージャー】クラス
*/
ResourceManager* MapManager::mpResourceManager = nullptr;
std::vector<ObjectBase*> MapManager::mpInitilizeObject = std::vector<ObjectBase*>();
// コンストラクタ
MapManager::MapManager()
: mpObjectManager(nullptr)
, mpCamera(nullptr)
, mstMapDatas(MapData::InitData())
, mstMapPosition(VECTOR_2D::Zero())
, mbStartupFlag(false)
{
    Master::mpDataManager->SetBitMapData("Resource/PerlinNoise.bmp");
}

// デストラクタ
MapManager::~MapManager()
{
}


// 初期化
void MapManager::Initilize()
{
    mpResourceManager = Master::mpResourceManager;
    mpObjectManager = Master::mpGameManager->GetObjectManager();
    mpCamera = Master::mpGameManager->GetCamera();

    mpInitilizeObject.clear();

    mstMapPosition = mpCamera->GetCameraPos() - (VECTOR_2D::GetIntVec(MAP_WIDTH_MAX, MAP_HEIGHT_MAX) * 0.5f);

    mstMapDatas = MapData::InitData();

    for (int y = 0; y < MAP_HEIGHT_MAX; y++)
    {
        MapManager::SetOneLine('Y', &mstMapDatas, MapChangeData::GetOneLineData(y,-1), mstMapPosition);
    }

    mbStartupFlag = true;
}

// 終了
void MapManager::Finalize()
{
}

// 更新
void MapManager::Update()
{
    if (mbStartupFlag)
    {
        for (int i = 0; i < mpInitilizeObject.size(); i++)
        {
            mpInitilizeObject[i]->Initilize();
        }
        mpInitilizeObject.clear();

    // マップの移動
    VECTOR_2D mapMove = (mpCamera->GetCameraPos() - (mstMapPosition + VECTOR_2D::GetIntVec(MAP_WIDTH_MAX, MAP_HEIGHT_MAX) * 0.5f));
    if (mapMove.SetInt2D() != 0)
    {
        mstMapPosition += mstMapDatas.NumberChange(mapMove, mstMapPosition);
    }

    // マップ効果キャラクターに反映
    /*VECTOR_2D drawPos = MapData::CheckRange(VECTOR_2D::GetIntVec(mstMapDatas.mapLeftUpPos.IntX() + 0, mstMapDatas.mapLeftUpPos.IntY() + 0));
    switch (mstMapDatas.ground[drawPos.IntY()][drawPos.IntX()])
    {
    case 0:
        break;
    }

    switch (mstMapDatas.mapObject[drawPos.IntY()][drawPos.IntX()])
    {
    case 0:
        break;
    }*/
    }
}

// 描画
void MapManager::Draw()
{
    if (mbStartupFlag)
    {
        for (int y = 0; y < MAP_HEIGHT_MAX; y++)
        {
            for (int x = 0; x < MAP_WIDTH_MAX; x++)
            {
                VECTOR_2D drawPos = MapData::CheckRange(VECTOR_2D::GetIntVec(x + mstMapDatas.mapLeftUpPos.IntX(), y + mstMapDatas.mapLeftUpPos.IntY())).SetInt2D();
                if (mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()] != -1)
                {
                    switch (mstMapDatas.ground[drawPos.IntY()][drawPos.IntX()])
                    {
                    case 0:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.0f, 0.125f, 0.0f, 0.125f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;

                    case 1:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.375f, 0.125f, 0.0f, 0.125f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;

                    case 2:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.125f, 0.125f, 0.0f, 0.125f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;

                    case 3:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.25f, 0.125f, 0.0f, 0.125f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;
                    }
                }

                if (mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()] != -1)
                {
                    switch (mstMapDatas.mapObject[drawPos.IntY()][drawPos.IntX()])
                    {
                    case 0:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.5f, 0.125f, 0.75f, 0.125f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;
                    }
                }
            }
        }
    }
}

// 1ライン変更処理
MapData MapManager::SetOneLine(const char XorYLine, MapData *src, MapChangeData changeData, VECTOR_2D mapPos)
{
    if (mpResourceManager == nullptr)
    {
        return *src;
    }

    switch (XorYLine)
    {
    case 'X':
    case 'x':
        if (changeData.SetLine.IntX() >= MAP_WIDTH_MAX)
        {
            changeData.SetLine.X -= MAP_WIDTH_MAX * (changeData.SetLine.IntX() / MAP_WIDTH_MAX);
        }
        else if (changeData.SetLine.IntX() < 0)
        {
            changeData.SetLine.X += MAP_WIDTH_MAX * (1 + ((changeData.SetLine.IntX() + 1) / -MAP_WIDTH_MAX));
        }
        for (int y = 0; y < MAP_HEIGHT_MAX; y++)
        {
            // リソース削除
            {
                if (src->mapResourceNumber[0][y][changeData.SetLine.IntX()] != -1)
                {
                    mpResourceManager->SubResource(src->mapResourceNumber[0][y][changeData.SetLine.IntX()]);
                }
                if (src->mapResourceNumber[1][y][changeData.SetLine.IntX()] != -1)
                {
                    mpResourceManager->SubResource(src->mapResourceNumber[1][y][changeData.SetLine.IntX()]);
                }
            }

            src->ground[y][changeData.SetLine.IntX()] = changeData.groundData[y];
            src->mapObject[y][changeData.SetLine.IntX()] = changeData.mapObjectData[y];

            // リソース設定 And 敵キャラ生成
            {
                switch (src->mapObject[y][changeData.SetLine.IntX()])
                {
                case 1:
                {
                    EnemyBase* enemy = new EnemyBase(VECTOR_2D::GetFloatVec(mapPos.X + changeData.SetLine.IntX(), mapPos.Y + y));
                    mpInitilizeObject.push_back(enemy);
                }
                break;
                }

                src->mapResourceNumber[0][y][changeData.SetLine.IntX()] = MapManager::GetGroundOrMapObject_ResourceNumber(src->ground[y][changeData.SetLine.IntX()]);
                src->mapResourceNumber[1][y][changeData.SetLine.IntX()] = MapManager::GetGroundOrMapObject_ResourceNumber(src->mapObject[y][changeData.SetLine.IntX()], false);
            }
        }
        break;

    case 'Y':
    case 'y':
        if (changeData.SetLine.IntY() >= MAP_HEIGHT_MAX)
        {
            changeData.SetLine.Y -= MAP_HEIGHT_MAX * (changeData.SetLine.IntY() / MAP_HEIGHT_MAX);
        }
        else if (changeData.SetLine.IntY() < 0)
        {
            changeData.SetLine.Y += MAP_HEIGHT_MAX * (1 + ((changeData.SetLine.IntY() + 1) / -MAP_HEIGHT_MAX));
        }
        for (int x = 0; x < MAP_WIDTH_MAX; x++)
        {
            // リソース削除
            {
                if (src->mapResourceNumber[0][changeData.SetLine.IntY()][x] != -1)
                {
                    mpResourceManager->SubResource(src->mapResourceNumber[0][changeData.SetLine.IntY()][x]);
                }
                if (src->mapResourceNumber[1][changeData.SetLine.IntY()][x] != -1)
                {
                    mpResourceManager->SubResource(src->mapResourceNumber[1][changeData.SetLine.IntY()][x]);
                }
            }

            src->ground[changeData.SetLine.IntY()][x] = changeData.groundData[x];
            src->mapObject[changeData.SetLine.IntY()][x] = changeData.mapObjectData[x];

            // リソース設定 And 敵キャラ生成
            {
                switch (src->mapObject[changeData.SetLine.IntY()][x])
                {
                case 1:
                {
                    EnemyBase* enemy = new EnemyBase(VECTOR_2D::GetFloatVec(mapPos.X + x, mapPos.Y + changeData.SetLine.IntY()));
                    mpInitilizeObject.push_back(enemy);
                }
                    break;
                }

                src->mapResourceNumber[0][changeData.SetLine.IntY()][x] = MapManager::GetGroundOrMapObject_ResourceNumber(src->ground[changeData.SetLine.IntY()][x]);
                src->mapResourceNumber[1][changeData.SetLine.IntY()][x] = MapManager::GetGroundOrMapObject_ResourceNumber(src->mapObject[changeData.SetLine.IntY()][x], false);
            }
        }
        break;
    }

    return *src;
}

// グラウンドもしくはマップオブジェクトのナンバーに合わせたリソースナンバーを返す
int MapManager::GetGroundOrMapObject_ResourceNumber(int number, bool groundFlag)
{
    int result = -1;

    if (groundFlag)
    {
        switch (number)
        {
        case 0:
            result = mpResourceManager->AddResource(L"Resource/mapchip.png");
            break;
        case 1:
            result = mpResourceManager->AddResource(L"Resource/mapchip.png");
            break;
        case 2:
            result = mpResourceManager->AddResource(L"Resource/mapchip.png");
            break;
        case 3:
            result = mpResourceManager->AddResource(L"Resource/mapchip.png");
            break;
        }
    }
    else
    {
        switch (number)
        {
        case 0:
            result = mpResourceManager->AddResource(L"Resource/mapchip.png");
            break;
        }
    }

    return result;
}

// 当たらない地点を返す
VECTOR_2D MapManager::GetNoHitPos(VECTOR_2D checkPos, VECTOR_2D srcPos, VECTOR_2D moveVec, VECTOR_2D srcSize)
{
	return VECTOR_2D::Zero();
}

/*
// 四角範囲描画
void MapManager::MapOneSquareDraw(float x, float y, float left, float right, float up, float down, int resourceId, unsigned int intFlag)
{
    mpResourceManager->DrawSprite(x * MAP_ONE_SQUARE_SIZE * mpCamera->GetNowOneLength().X, y * MAP_ONE_SQUARE_SIZE * mpCamera->GetNowOneLength().Y, MAP_ONE_SQUARE_SIZE * mpCamera->GetNowOneLength().X, MAP_ONE_SQUARE_SIZE * mpCamera->GetNowOneLength().Y, left, right, up, down, resourceId, intFlag);
}*/