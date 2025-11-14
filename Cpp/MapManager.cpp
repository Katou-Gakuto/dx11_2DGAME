#include <vector>
#include <string.h>
#include <cstdlib>
#include <ctime>

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
    // シード値を現在の時刻で初期化
    srand(static_cast<unsigned int>(time(0)));

    MapChangeData initDat;
    memset(initDat.groundData, 0, sizeof(initDat.groundData));
    memset(initDat.mapObjectData, 0, sizeof(initDat.mapObjectData));
    initDat.SetLine = VECTOR_2D::Zero();
    return initDat;
}

/*一列分のデータ取得*/
MapChangeData MapChangeData::GetOneLineData(int lineNumber, int lineType = 0, VECTOR_2D pos = VECTOR_2D::Zero())
{
    MapChangeData oneLineData = MapChangeData::InitData();

#if MAP_CREATE_TYPE == 0
    switch (lineType)
    {
    case -1:
    {
        const unsigned long setLine[2][ARRAY_SIZE] = {
            {   (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN,
                (unsigned long)GROUND_TYPE::PLAIN, (unsigned long)GROUND_TYPE::PLAIN
            },
            {   (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::FLOWER
            }
        };

        memcpy(oneLineData.groundData, setLine[0], sizeof(oneLineData.groundData));
        memcpy(oneLineData.mapObjectData, setLine[1], sizeof(oneLineData.mapObjectData));
    }
    break;

    case 0:
    {
        const unsigned long setLine[2][ARRAY_SIZE] = {
            {   (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::WETLAND, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT
            },
            {   (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::ENEMY, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::ENEMY, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::ENEMY, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::FLOWER,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::FLOWER, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT
            }
        };

        memcpy(oneLineData.groundData, setLine[0], sizeof(oneLineData.groundData));
        memcpy(oneLineData.mapObjectData, setLine[1], sizeof(oneLineData.mapObjectData));
    }
    break;

    default:
    {
        const unsigned long setLine[2][ARRAY_SIZE] = {
            {   (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT,
                (unsigned long)GROUND_TYPE::DEFAULT, (unsigned long)GROUND_TYPE::DEFAULT
            },
            {   (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT,
                (unsigned long)MAP_OBJECT_TYPE::DEFAULT, (unsigned long)MAP_OBJECT_TYPE::DEFAULT
            }
        };

        memcpy(oneLineData.groundData, setLine[0], sizeof(oneLineData.groundData));
        memcpy(oneLineData.mapObjectData, setLine[1], sizeof(oneLineData.mapObjectData));
    }
    break;
    }

#elif MAP_CREATE_TYPE == 1
    switch (lineType)
    {
    case -1:// 下移動
        for (int x = 0; x < MAP_WIDTH_MAX; x++)
        {
            oneLineData.groundData[x] = Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(x, MAP_HEIGHT_MAX)).blue;
            oneLineData.mapObjectData[x] = Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(x, MAP_HEIGHT_MAX)).blue;
            
            if (Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(x, MAP_HEIGHT_MAX)).blue > 0)
            {
                oneLineData.groundData[x] = (unsigned long)GROUND_TYPE::PLAIN;
            }
            if (Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(x, MAP_HEIGHT_MAX)).blue > 0)
            {
                oneLineData.mapObjectData[x] = (unsigned long)MAP_OBJECT_TYPE::ENEMY;
            }
        }
        break;

    case -2:// 上移動
        for (int x = 0; x < MAP_WIDTH_MAX; x++)
        {
            oneLineData.groundData[x] = Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(x, 0)).blue;
            oneLineData.mapObjectData[x] = Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(x, 0)).blue;
            
            if (Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(x, 0)).blue > 0)
            {
                oneLineData.groundData[x] = (unsigned long)GROUND_TYPE::PLAIN;
            }
            if (Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(x, 0)).blue > 0)
            {
                oneLineData.mapObjectData[x] = (unsigned long)MAP_OBJECT_TYPE::ENEMY;
            }
        }
        break;

    case -3:// 右移動
        for (int y = 0; y < MAP_HEIGHT_MAX; y++)
        {
            oneLineData.groundData[y] = Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(0, y)).blue;
            oneLineData.mapObjectData[y] = Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(0, y)).blue;
            
            if (Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(0, y)).blue > 0)
            {
                oneLineData.groundData[y] = (unsigned long)GROUND_TYPE::PLAIN;
            }
            if (Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(0, y)).blue > 0)
            {
                oneLineData.mapObjectData[y] = (unsigned long)MAP_OBJECT_TYPE::ENEMY;
            }
        }
        break;

    case -4:// 左移動
        for (int y = 0; y < MAP_HEIGHT_MAX; y++)
        {
            oneLineData.groundData[y] = Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(MAP_WIDTH_MAX, y)).blue;
            oneLineData.mapObjectData[y] = Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(MAP_WIDTH_MAX, y)).blue;
            
            if (Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(MAP_WIDTH_MAX, y)).blue > 0)
            {
                oneLineData.groundData[y] = (unsigned long)GROUND_TYPE::PLAIN;
            }
            if (Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(MAP_WIDTH_MAX, y)).blue > 0)
            {
                oneLineData.mapObjectData[y] = (unsigned long)MAP_OBJECT_TYPE::ENEMY;
            }
        }
        break;
    }
#endif

    oneLineData.SetLine = (float)lineNumber;

    return oneLineData;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【マップデータ】構造体
*/
// コンストラクタ
MapData::MapData()
{
    memset(ground, 0, sizeof(ground));
    memset(mapObject, 0, sizeof(mapObject));
    memset(mapResourceNumber, 0, sizeof(mapResourceNumber));
    mapLeftUpPos = 0;
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

#if MAP_CREATE_TYPE == 0
    if (changeVolume.Y > 0.0f)
    {
        for (int y = 0; y < changeVolume.IntY(); y++)
        {
            MapManager::SetOneLine('Y', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntY() + y, Master::mpDataManager->GetBitMapData()[0].GetMapPixel(false).blue), mapPos, true);
            moveNumber.Y += 1.0f;
        }
    }
    else if (changeVolume.Y < 0.0f)
    {
        for (int y = -1; y > changeVolume.IntY() - 1; y--)
        {
            MapManager::SetOneLine('Y', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntY() + y, Master::mpDataManager->GetBitMapData()[0].GetMapPixel(false).blue), mapPos, false);
            moveNumber.Y -= 1.0f;
        }
    }

    if (changeVolume.X > 0.0f)
    {
        for (int x = 0; x < changeVolume.IntX(); x++)
        {
            MapManager::SetOneLine('X', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntX() + x, Master::mpDataManager->GetBitMapData()[0].GetMapPixel(true).blue), mapPos, true);
            moveNumber.X += 1.0f;
        }
    }
    else if (changeVolume.X < 0.0f)
    {
        for (int x = -1; x > changeVolume.IntX() - 1; x--)
        {
            MapManager::SetOneLine('X', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntX() + x, Master::mpDataManager->GetBitMapData()[0].GetMapPixel(true).blue), mapPos, false);
            moveNumber.X -= 1.0f;
        }
    }
#elif MAP_CREATE_TYPE == 1
    if (changeVolume.Y > 0.0f)
    {
        for (int y = 0; y < changeVolume.IntY(); y++)
        {
            MapManager::SetOneLine('Y', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntY() + y, -1, mapPos), mapPos, true);
            moveNumber.Y += 1.0f;
        }
    }
    else if (changeVolume.Y < 0.0f)
    {
        for (int y = -1; y > changeVolume.IntY() - 1; y--)
        {
            MapManager::SetOneLine('Y', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntY() + y, -2, mapPos), mapPos, false);
            moveNumber.Y -= 1.0f;
        }
    }

    if (changeVolume.X > 0.0f)
    {
        for (int x = 0; x < changeVolume.IntX(); x++)
        {
            MapManager::SetOneLine('X', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntX() + x, -3, mapPos), mapPos, true);
            moveNumber.X += 1.0f;
        }
    }
    else if (changeVolume.X < 0.0f)
    {
        for (int x = -1; x > changeVolume.IntX() - 1; x--)
        {
            MapManager::SetOneLine('X', this, MapChangeData::GetOneLineData(this->mapLeftUpPos.IntX() + x, -4), mapPos, false);
            moveNumber.X -= 1.0f;
        }
    }
#endif

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
, mstMapDatas(MapData())
, mstMapPosition(VECTOR_2D::Zero())
, mbStartupFlag(false)
{
    Master::mpDataManager->SetBitMapData("Resource/PerlinNoise.bmp");
#if MAP_CREATE_TYPE == 1
    Master::mpDataManager->SetBitMapData("Resource/PerlinNoise.bmp");
#endif
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

    mstMapDatas = MapData();

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
                    switch ((GROUND_TYPE)(mstMapDatas.ground[drawPos.IntY()][drawPos.IntX()] & 0xf))
                    {
                    case GROUND_TYPE::PLAIN:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.0f, 0.125f, 0.0f, 0.125f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;
                        
                    case GROUND_TYPE::FOREST:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.375f, 0.125f, 0.0f, 0.125f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;

                    case GROUND_TYPE::SAVANNA:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.125f, 0.125f, 0.0f, 0.125f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;

                    case GROUND_TYPE::DESERT:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.25f, 0.125f, 0.0f, 0.125f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;

                    case GROUND_TYPE::SNOWFIELD:
                        break;

                    case GROUND_TYPE::VOLCANIC:
                        break;

                    case GROUND_TYPE::WETLAND:
                        break;
                    }
                }

                if (mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()] != -1)
                {
                    switch ((MAP_OBJECT_TYPE)(mstMapDatas.mapObject[drawPos.IntY()][drawPos.IntX()] & 0xf))
                    {
                    case MAP_OBJECT_TYPE::TREE:
                    case MAP_OBJECT_TYPE::ROCK:
                    case MAP_OBJECT_TYPE::BUSH:
                    case MAP_OBJECT_TYPE::MOUNTAIN:
                    case MAP_OBJECT_TYPE::WATER_PUDDLE:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.5f, 0.125f, 0.75f, 0.125f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;

                    case MAP_OBJECT_TYPE::FLOWER:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.5f, 0.125f, 0.75f, 0.125f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;
                    }
                }
            }
        }
    }
}

// 1ライン変更処理
MapData MapManager::SetOneLine(const char XorYLine, MapData *src, MapChangeData changeData, VECTOR_2D mapPos, bool plusFlag)
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
            if (plusFlag)
            {
                SetOneTile(src, VECTOR_2D(changeData.SetLine.IntX(), y), mapPos, changeData.groundData[y], changeData.mapObjectData[y], { 3, 1, 0, 5 });
            }
            else
            {
                SetOneTile(src, VECTOR_2D(changeData.SetLine.IntX(), y), mapPos, changeData.groundData[y], changeData.mapObjectData[y], { 4, 1, 2, 7 });
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
            if (plusFlag)
            {
                SetOneTile(src, VECTOR_2D(x, changeData.SetLine.IntY()), mapPos, changeData.groundData[x], changeData.mapObjectData[x], { 1, 3, 0, 2 });
            }
            else
            {
                SetOneTile(src, VECTOR_2D(x, changeData.SetLine.IntY()), mapPos, changeData.groundData[x], changeData.mapObjectData[x], { 6, 3, 5, 7 });
            }
        }
        break;
    }

    return *src;
}

/*1タイル分の変更処理*/
void MapManager::SetOneTile(MapData* src, VECTOR_2D mapPos, VECTOR_2D createPos, unsigned long groundNumber, unsigned long mapObjectNumber, std::vector<int> checkVecs)
{
    static const VECTOR_2D mapCheckVec[8] = { VECTOR_2D(-1, -1), VECTOR_2D(0, -1), VECTOR_2D(1, -1),
                                                VECTOR_2D(-1, 0),                    VECTOR_2D(1, 0),
                                                VECTOR_2D(-1, 1),  VECTOR_2D(0, 1),  VECTOR_2D(1, 1) };

    // リソース削除
    {
        if (src->mapResourceNumber[0][mapPos.IntY()][mapPos.IntX()] != -1)
        {
            mpResourceManager->SubResource(src->mapResourceNumber[0][mapPos.IntY()][mapPos.IntX()]);
        }
        if (src->mapResourceNumber[1][mapPos.IntY()][mapPos.IntX()] != -1)
        {
            mpResourceManager->SubResource(src->mapResourceNumber[1][mapPos.IntY()][mapPos.IntX()]);
        }
    }

    // マップ変更(変更前の周辺確認後で)
    {
        unsigned long plusData = 0;
        unsigned long count = 0;

        switch ((GROUND_TYPE)(groundNumber & 0xf))
        {
#if MAP_CREATE_TYPE == 0
        case GROUND_TYPE::DEFAULT:
        {
            bool setFlag = false;
            for (int i = 0; i < checkVecs.size(); i++)
            {
                VECTOR_2D checkPos = MapData::CheckRange(mapCheckVec[checkVecs[i]] + mapPos).SetInt2D();
                if (((src->ground[checkPos.IntY()][checkPos.IntX()] & (0xff << 8)) != 0) && ((src->ground[checkPos.IntY()][checkPos.IntX()] & (0xff << 8)) != 1))
                {
                    src->ground[mapPos.IntY()][mapPos.IntX()] = (((((src->ground[checkPos.IntY()][checkPos.IntX()] >> 8) & 0xff) - 1) << 8) | (src->ground[checkPos.IntY()][checkPos.IntX()] & 0xff) | GetDifferentFlag(src->ground, mapPos, src->ground[checkPos.IntY()][checkPos.IntX()] & 0xf));
                    setFlag = true;
                    break;
                }
            }
            if (!setFlag)
            {
                src->ground[mapPos.IntY()][mapPos.IntX()] = (int)GROUND_TYPE::PLAIN;
            }
        }
        break;

        case GROUND_TYPE::VOLCANIC:
            ++count;
        case GROUND_TYPE::SNOWFIELD:
            ++count;
        case GROUND_TYPE::DESERT:
            ++count;
        case GROUND_TYPE::WETLAND:
            ++count;
        case GROUND_TYPE::SAVANNA:
            ++count;
        case GROUND_TYPE::FOREST:
            ++count;
        case GROUND_TYPE::PLAIN:
            ++count;

            plusData = ((count << 4) | ((unsigned long)(rand() & 0xff) << 8) | GetDifferentFlag(src->ground, mapPos, groundNumber));
            src->ground[mapPos.IntY()][mapPos.IntX()] = (groundNumber | plusData);
            break;

#elif MAP_CREATE_TYPE == 1
        case GROUND_TYPE::VOLCANIC:
        case GROUND_TYPE::SNOWFIELD:
        case GROUND_TYPE::DESERT:
        case GROUND_TYPE::WETLAND:
        case GROUND_TYPE::SAVANNA:
        case GROUND_TYPE::FOREST:
        case GROUND_TYPE::PLAIN:
        case GROUND_TYPE::DEFAULT:
            src->ground[mapPos.IntY()][mapPos.IntX()] = (groundNumber | GetDifferentFlag(src->ground, mapPos, groundNumber));
            break;

#endif
        }

        plusData = 0;
        switch ((MAP_OBJECT_TYPE)(mapObjectNumber & 0xf))
        {
#if MAP_CREATE_TYPE == 0
        case MAP_OBJECT_TYPE::DEFAULT:
        {
            bool setFlag = false;
            for (int i = 0; i < checkVecs.size(); i++)
            {
                VECTOR_2D checkPos = MapData::CheckRange(mapCheckVec[checkVecs[i]] + mapPos).SetInt2D();

                if (((src->mapObject[checkPos.IntY()][checkPos.IntX()] & (0xff << 8)) != 0) && ((src->mapObject[checkPos.IntY()][checkPos.IntX()] & (0xff << 8)) != 1))
                {
                    src->mapObject[mapPos.IntY()][mapPos.IntX()] = (((((src->mapObject[checkPos.IntY()][checkPos.IntX()] >> 8) & 0xff) - 1) << 8) | (src->ground[mapPos.IntY()][mapPos.IntX()] & (0xf << 4)) | (src->mapObject[checkPos.IntY()][checkPos.IntX()] & 0xf) | GetDifferentFlag(src->mapObject, mapPos, src->mapObject[checkPos.IntY()][checkPos.IntX()] & 0xf));
                    setFlag = true;
                    break;
                }
            }
            if (!setFlag)
            {
                src->mapObject[mapPos.IntY()][mapPos.IntX()] = (int)MAP_OBJECT_TYPE::NONE;
            }
        }
        break;

        case MAP_OBJECT_TYPE::WATER_PUDDLE:
        case MAP_OBJECT_TYPE::MOUNTAIN:
        case MAP_OBJECT_TYPE::BUSH:
        case MAP_OBJECT_TYPE::ROCK:
        case MAP_OBJECT_TYPE::TREE:
        case MAP_OBJECT_TYPE::NONE:
        case MAP_OBJECT_TYPE::FLOWER:

            plusData = ((src->ground[mapPos.IntY()][mapPos.IntX()] & (0xf << 4)) | ((unsigned long)(rand() & 0xff) << 8) | GetDifferentFlag(src->ground, mapPos, mapObjectNumber));
            src->mapObject[mapPos.IntY()][mapPos.IntX()] = (mapObjectNumber | plusData);

            break;
#elif MAP_CREATE_TYPE == 1
        case MAP_OBJECT_TYPE::DEFAULT:
        case MAP_OBJECT_TYPE::ENEMY:
        case MAP_OBJECT_TYPE::WATER_PUDDLE:
        case MAP_OBJECT_TYPE::MOUNTAIN:
        case MAP_OBJECT_TYPE::BUSH:
        case MAP_OBJECT_TYPE::ROCK:
        case MAP_OBJECT_TYPE::TREE:
        case MAP_OBJECT_TYPE::NONE:
        case MAP_OBJECT_TYPE::FLOWER:
            src->mapObject[mapPos.IntY()][mapPos.IntX()] = (mapObjectNumber | GetDifferentFlag(src->mapObject, mapPos, groundNumber));
            break;

#endif
        }

    }

    // リソース設定 And 敵キャラ生成
    {
        switch ((MAP_OBJECT_TYPE)(src->mapObject[mapPos.IntY()][mapPos.IntX()] & 0xf))
        {
        case MAP_OBJECT_TYPE::ENEMY:
        {
            EnemyBase* enemy = new EnemyBase(VECTOR_2D::GetFloatVec(createPos.X + mapPos.IntX(), createPos.Y + mapPos.IntY()));
            mpInitilizeObject.push_back(enemy);
        }
        break;
        }

        src->mapResourceNumber[0][mapPos.IntY()][mapPos.IntX()] = MapManager::GetGroundOrMapObject_ResourceNumber(src->ground[mapPos.IntY()][mapPos.IntX()]);
        src->mapResourceNumber[1][mapPos.IntY()][mapPos.IntX()] = MapManager::GetGroundOrMapObject_ResourceNumber(src->mapObject[mapPos.IntY()][mapPos.IntX()], false);
    }
}
// 隣接タイルが違う種類が有効なフラグを返す
unsigned long MapManager::GetDifferentFlag(unsigned long src[38][62], VECTOR_2D targetPos, unsigned long targettype)
{
    return 0ul;
}

// グラウンドもしくはマップオブジェクトのナンバーに合わせたリソースナンバーを返す
int MapManager::GetGroundOrMapObject_ResourceNumber(int number, bool groundFlag)
{
    int result = -1;

    if (groundFlag)
    {
        switch ((GROUND_TYPE)(number & 0xf))
        {
        case GROUND_TYPE::DEFAULT:
        case GROUND_TYPE::DESERT:
        case GROUND_TYPE::FOREST:
        case GROUND_TYPE::PLAIN:
        case GROUND_TYPE::SAVANNA:
        case GROUND_TYPE::SNOWFIELD:
        case GROUND_TYPE::VOLCANIC:
        case GROUND_TYPE::WETLAND:

            result = mpResourceManager->AddResource(L"Resource/mapchip.png");
            break;
        }
    }
    else
    {
        switch ((MAP_OBJECT_TYPE)(number & 0xf))
        {
        case MAP_OBJECT_TYPE::DEFAULT:
        case MAP_OBJECT_TYPE::FLOWER:
        case MAP_OBJECT_TYPE::TREE:
        case MAP_OBJECT_TYPE::ROCK:
        case MAP_OBJECT_TYPE::BUSH:
        case MAP_OBJECT_TYPE::MOUNTAIN:
        case MAP_OBJECT_TYPE::WATER_PUDDLE:
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