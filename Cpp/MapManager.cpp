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
#include "../Header/TargetDatas.h"
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

    if (MapCreateType == 0)
    {
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
    }
    else if (MapCreateType == 1)
    {
        switch (lineType)
        {
        case -1:// 下移動
            for (int x = 0; x < MAP_WIDTH_MAX; x++)
            {
                unsigned char groundNumber = Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(x, MAP_HEIGHT_MAX)).blue;
                unsigned char mapObjectNumber = Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(x, MAP_HEIGHT_MAX)).blue;

                oneLineData.groundData[x] = (unsigned long)GetGroundType(groundNumber);
                oneLineData.mapObjectData[x] = (unsigned long)GetMapObjectType(mapObjectNumber);
            }
            break;

        case -2:// 上移動
            for (int x = 0; x < MAP_WIDTH_MAX; x++)
            {
                unsigned char groundNumber = Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(x, 0)).blue;
                unsigned char mapObjectNumber = Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(x, 0)).blue;

                oneLineData.groundData[x] = (unsigned long)GetGroundType(groundNumber);
                oneLineData.mapObjectData[x] = (unsigned long)GetMapObjectType(mapObjectNumber);
            }
            break;

        case -3:// 右移動
            for (int y = 0; y < MAP_HEIGHT_MAX; y++)
            {
                unsigned char groundNumber = Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(0, y)).blue;
                unsigned char mapObjectNumber = Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(0, y)).blue;

                oneLineData.groundData[y] = (unsigned long)GetGroundType(groundNumber);
                oneLineData.mapObjectData[y] = (unsigned long)GetMapObjectType(mapObjectNumber);
            }
            break;

        case -4:// 左移動
            for (int y = 0; y < MAP_HEIGHT_MAX; y++)
            {
                unsigned char groundNumber = Master::mpDataManager->GetBitMapData()[0].GetMapPixel(pos + VECTOR_2D(MAP_WIDTH_MAX, y)).blue;
                unsigned char mapObjectNumber = Master::mpDataManager->GetBitMapData()[1].GetMapPixel(pos + VECTOR_2D(MAP_WIDTH_MAX, y)).blue;

                oneLineData.groundData[y] = (unsigned long)GetGroundType(groundNumber);
                oneLineData.mapObjectData[y] = (unsigned long)GetMapObjectType(mapObjectNumber);
            }
            break;
        }
    }

    oneLineData.SetLine = (float)lineNumber;

    return oneLineData;
}

// 地面データタイプ取得
GROUND_TYPE MapChangeData::GetGroundType(unsigned char number)
{
    if (number < 80)
    {
        return GROUND_TYPE::SNOWFIELD;
    }
    else if (number < 190)
    {
        return GROUND_TYPE::PLAIN;
    }
    else if (number < 256)
    {
        return GROUND_TYPE::WETLAND;
    }
    // else if (number < 160)
    // {
    //     return GROUND_TYPE::FOREST;
    // }
    // else if (number < 200)
    // {
    //     return GROUND_TYPE::SAVANNA;
    // }
    // else if (number < 240)
    // {
    //     return GROUND_TYPE::DESERT;
    // }
    // else if (number < 256)
    // {
    //     return GROUND_TYPE::VOLCANIC;
    // }

    return GROUND_TYPE::DEFAULT;
}

// 地マップオブジェクトタイプ取得
MAP_OBJECT_TYPE MapChangeData::GetMapObjectType(unsigned char number)
{
    if (number < 40)
    {
        return MAP_OBJECT_TYPE::ENEMY;
    }
    else if (number < 150)
    {
        if ((number % 2) != 0)
        {
            return MAP_OBJECT_TYPE::FLOWER;
        }
        else
        {
            return MAP_OBJECT_TYPE::NONE;
        }
    }
    else if (number < 200)
    {
        return MAP_OBJECT_TYPE::WATER_PUDDLE;
    }
    else if (number < 210)
    {
        return MAP_OBJECT_TYPE::NONE;
    }
    else if (number < 256)
    {
        return MAP_OBJECT_TYPE::WATER_PUDDLE;
    }
    // else if (number < 90)
    // {
    //     return MAP_OBJECT_TYPE::BUSH;
    // }
    // else if (number < 180)
    // {
    //     return MAP_OBJECT_TYPE::ROAD;
    // }
    // else if (number < 256)
    // {
    //     return MAP_OBJECT_TYPE::MOUNTAIN;
    // }

    return MAP_OBJECT_TYPE::DEFAULT;
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

    if (MapCreateType == 0)
    {
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
    }
    else if (MapCreateType == 1)
    {
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
, mstMapDatas(MapData())
, mstMapPosition(VECTOR_2D::Zero())
, mbStartupFlag(false)
{
    Master::mpDataManager->SetBitMapData("Resource/PerlinNoise.bmp");
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

    MapCreateType = 0;

    mstMapPosition = mpCamera->GetCameraPos() - (VECTOR_2D::GetIntVec(MAP_WIDTH_MAX, MAP_HEIGHT_MAX) * 0.5f);

    mstMapDatas = MapData();

    for (int y = 0; y < MAP_HEIGHT_MAX; y++)
    {
        MapManager::SetOneLine('Y', &mstMapDatas, MapChangeData::GetOneLineData(y, -1), mstMapPosition);
    }
    MapCreateType = 1;

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
        // プレイヤーキャラクターに反映
        for (auto& player : Master::mpGameManager->GetTargetDatas()->GetPlayers())
        {
            player->GetStatus().Flag = 0;

            VECTOR_2D checkPos = MapData::CheckRange(VECTOR_2D::GetIntVec(player->GetStatus().Position.IntX() + (MAP_WIDTH_MAX * 0.5f), player->GetStatus().Position.IntY() + (MAP_HEIGHT_MAX * 0.5f)));
            switch ((GROUND_TYPE)(mstMapDatas.ground[checkPos.IntY()][checkPos.IntX()] & 0xf))
            {
            case GROUND_TYPE::DEFAULT:
                break;
            }

            switch ((MAP_OBJECT_TYPE)(mstMapDatas.mapObject[checkPos.IntY()][checkPos.IntX()] & 0xf))
            {
            case MAP_OBJECT_TYPE::WATER_PUDDLE:
                player->GetStatus().Flag |= (unsigned long)SET_STATUS_FLAG::SLOW_FLAG;
                break;
            }

            player->GetStatus().SetLevelStatus();
        }
        // 敵キャラクターに反映
        for (auto& enemy : Master::mpGameManager->GetTargetDatas()->GetEnemys())
        {
            enemy->GetStatus().Flag = 0;

            VECTOR_2D checkPos = MapData::CheckRange(VECTOR_2D::GetIntVec(enemy->GetStatus().Position.IntX() + (MAP_WIDTH_MAX * 0.5f), enemy->GetStatus().Position.IntY() + (MAP_HEIGHT_MAX * 0.5f)));
            switch ((GROUND_TYPE)(mstMapDatas.ground[checkPos.IntY()][checkPos.IntX()] & 0xf))
            {
            case GROUND_TYPE::DEFAULT:
                break;
            }

            switch ((MAP_OBJECT_TYPE)(mstMapDatas.mapObject[checkPos.IntY()][checkPos.IntX()] & 0xf))
            {
            case MAP_OBJECT_TYPE::WATER_PUDDLE:
                enemy->GetStatus().Flag |= (unsigned long)SET_STATUS_FLAG::SLOW_FLAG;
                break;
            }

            enemy->GetStatus().SetLevelStatus();
        }
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
                        break;

                    case GROUND_TYPE::DESERT:
                        break;

                    case GROUND_TYPE::SNOWFIELD:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.0f, 0.125f, 0.8f, 0.2f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                        break;

                    case GROUND_TYPE::VOLCANIC:
                        break;

                    case GROUND_TYPE::WETLAND:
                        mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.375f, 0.125f, 0.0f, 0.125f, mstMapDatas.mapResourceNumber[0][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
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
                        switch ((GROUND_TYPE)(mstMapDatas.ground[drawPos.IntY()][drawPos.IntX()] & 0xf))
                        {

                        case GROUND_TYPE::DEFAULT:
                        case GROUND_TYPE::DESERT:
                        case GROUND_TYPE::FOREST:
                        case GROUND_TYPE::SAVANNA:
                        case GROUND_TYPE::SNOWFIELD:
                        case GROUND_TYPE::VOLCANIC:
                            break;
                        case GROUND_TYPE::PLAIN:
                        case GROUND_TYPE::WETLAND:
                            // ビット方向メモ
                            /*0b0000'0000*/
                            /*0b右下、下、左下、右、'左、右上、上、左上*/

                            // 左上、上、左の3方向を確認
                            switch ((mstMapDatas.mapObject[drawPos.IntY()][drawPos.IntX()] >> 16) & 0b0000'1011)
                            {
                            case 0b0000'0000:// なし
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.8f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0000'0001:// 左上
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.6f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0000'0010:// 上
                            case 0b0000'0011:// 左上と上
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.4f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0000'1011:// 左上と上と左
                            case 0b0000'1010:// 上と左
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.0f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0000'1000:// 左
                            case 0b0000'1001:// 左上と左
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.2f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            }

                            // 右上、右、右下の3方向を確認
                            switch ((mstMapDatas.mapObject[drawPos.IntY()][drawPos.IntX()] >> 16) & 0b0001'0110)
                            {
                            case 0b0000'0000:// なし
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.8f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0000'0100:// 右上
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.6f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0000'0010:// 上
                            case 0b0000'0110:// 右上と上
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.4f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0001'0110:// 右上と上と右
                            case 0b0001'0010:// 上と右
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.0f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0001'0000:// 右
                            case 0b0001'0100:// 右上と右
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y - 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.2f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            }

                            // 左下、下、左の3方向を確認
                            switch ((mstMapDatas.mapObject[drawPos.IntY()][drawPos.IntX()] >> 16) & 0b0110'1000)
                            {
                            case 0b0000'0000:// なし
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.9f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0010'0000:// 左下
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.7f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0100'0000:// 下
                            case 0b0110'0000:// 左下と下
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.5f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0110'1000:// 左下と下と左
                            case 0b0100'1000:// 下と左
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.1f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0000'1000:// 左
                            case 0b0010'1000:// 左下と左
                                mpResourceManager->DrawSprite(x + mstMapPosition.X - 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0f, 0.0625f, 0.3f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            }

                            // 右下、下、右の3方向を確認
                            switch ((mstMapDatas.mapObject[drawPos.IntY()][drawPos.IntX()] >> 16) & 0b1101'0000)
                            {
                            case 0b0000'0000:// なし
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.9f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b1000'0000:// 右下
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.7f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0100'0000:// 下
                            case 0b1100'0000:// 右下と下
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.5f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b1101'0000:// 右下と下と右
                            case 0b0101'0000:// 下と右
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.1f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            case 0b0001'0000:// 右
                            case 0b1001'0000:// 右下と右
                                mpResourceManager->DrawSprite(x + mstMapPosition.X + 0.25f, y + mstMapPosition.Y + 0.25f, 0.5f, 0.5f, 0.0625f, 0.0625f, 0.3f, 0.1f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
                                break;
                            }
                        }
                    case MAP_OBJECT_TYPE::ROAD:
                        //mpResourceManager->DrawSprite(x + mstMapPosition.X, y + mstMapPosition.Y, 1.0f, 1.0f, 0.5f, 0.125f, 0.75f, 0.125f, mstMapDatas.mapResourceNumber[1][drawPos.IntY()][drawPos.IntX()], ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG | MIDDLE_FLAG);
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
                SetOneTile(src, VECTOR_2D(changeData.SetLine.IntX(), y), mapPos + VECTOR_2D(MAP_WIDTH_MAX, y), changeData.groundData[y], changeData.mapObjectData[y], { 3, 1, 0, 5 });
            }
            else
            {
                SetOneTile(src, VECTOR_2D(changeData.SetLine.IntX(), y), mapPos + VECTOR_2D(0, y), changeData.groundData[y], changeData.mapObjectData[y], { 4, 1, 2, 7 });
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
                SetOneTile(src, VECTOR_2D(x, changeData.SetLine.IntY()), mapPos + VECTOR_2D(x, MAP_HEIGHT_MAX), changeData.groundData[x], changeData.mapObjectData[x], {1, 3, 0, 2});
            }
            else
            {
                SetOneTile(src, VECTOR_2D(x, changeData.SetLine.IntY()), mapPos + VECTOR_2D(x, 0), changeData.groundData[x], changeData.mapObjectData[x], { 6, 3, 5, 7 });
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

        if (MapCreateType == 0)
        {
            switch ((GROUND_TYPE)(groundNumber & 0xf))
            {
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
            }
        }
        else if (MapCreateType == 1)
        {
            switch ((GROUND_TYPE)(groundNumber & 0xf))
            {
            case GROUND_TYPE::VOLCANIC:
            case GROUND_TYPE::SNOWFIELD:
            case GROUND_TYPE::DESERT:
            case GROUND_TYPE::WETLAND:
            case GROUND_TYPE::SAVANNA:
            case GROUND_TYPE::FOREST:
            case GROUND_TYPE::PLAIN:
            case GROUND_TYPE::DEFAULT:
                src->ground[mapPos.IntY()][mapPos.IntX()] = (groundNumber | GetDifferentFlag(src->ground, mapPos, groundNumber) | (groundNumber << 4));
                break;
            }
        }

        plusData = 0;
        if (MapCreateType == 0)
        {
            switch ((MAP_OBJECT_TYPE)(mapObjectNumber & 0xf))
            {
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

            case MAP_OBJECT_TYPE::ROAD:
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

            default:
                src->mapObject[mapPos.IntY()][mapPos.IntX()] = (mapObjectNumber | GetDifferentFlag(src->mapObject, mapPos, mapObjectNumber) | (src->ground[mapPos.IntY()][mapPos.IntX()] & (0xf << 4)));
                break;
            }
        }
        else if (MapCreateType == 1)
        {
            switch ((MAP_OBJECT_TYPE)(mapObjectNumber & 0xf))
            {
            case MAP_OBJECT_TYPE::DEFAULT:
            case MAP_OBJECT_TYPE::ENEMY:
            case MAP_OBJECT_TYPE::ROAD:
            case MAP_OBJECT_TYPE::WATER_PUDDLE:
            case MAP_OBJECT_TYPE::MOUNTAIN:
            case MAP_OBJECT_TYPE::BUSH:
            case MAP_OBJECT_TYPE::ROCK:
            case MAP_OBJECT_TYPE::TREE:
            case MAP_OBJECT_TYPE::NONE:
            case MAP_OBJECT_TYPE::FLOWER:
                src->mapObject[mapPos.IntY()][mapPos.IntX()] = (mapObjectNumber | GetDifferentFlag(src->mapObject, mapPos, mapObjectNumber) | (src->ground[mapPos.IntY()][mapPos.IntX()] & (0xf << 4)));
                break;

            default:
                src->mapObject[mapPos.IntY()][mapPos.IntX()] = (mapObjectNumber | GetDifferentFlag(src->mapObject, mapPos, mapObjectNumber) | (src->ground[mapPos.IntY()][mapPos.IntX()] & (0xf << 4)));
                break;

            }
        }

    }

    // リソース設定 And 敵キャラ生成
    {
        switch ((MAP_OBJECT_TYPE)(src->mapObject[mapPos.IntY()][mapPos.IntX()] & 0xf))
        {
        case MAP_OBJECT_TYPE::ENEMY:
        {
            EnemyBase* enemy = new EnemyBase(VECTOR_2D::GetFloatVec(createPos.X, createPos.Y));
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
    static const VECTOR_2D mapCheckVec[8] = { VECTOR_2D(-1, -1), VECTOR_2D(0, -1), VECTOR_2D(1, -1),
                                              VECTOR_2D(-1, 0),                    VECTOR_2D(1, 0),
                                              VECTOR_2D(-1, 1),  VECTOR_2D(0, 1),  VECTOR_2D(1, 1) };

    static const unsigned long mapFlagNumber[8] = {0b0000'0001ul << 16, 0b0000'0010ul << 16, 0b0000'0100ul << 16,
                                                   0b0000'1000ul << 16,                      0b0001'0000ul << 16,
                                                   0b0010'0000ul << 16, 0b0100'0000ul << 16, 0b1000'0000ul << 16 };

    unsigned long result = 0ul;
    
    for (int i = 0; i < 8; i++)
    {
        VECTOR_2D pos = MapData::CheckRange(VECTOR_2D((int)mapCheckVec[i].X + targetPos.IntX(), (int)mapCheckVec[i].Y + targetPos.IntY()));
        if ((src[pos.IntY()][pos.IntX()] & 0xf) != (targettype & 0xf))
        {
            result |= mapFlagNumber[i];
            src[pos.IntY()][pos.IntX()] |= mapFlagNumber[7 - i];
        }
        else
        {
            src[pos.IntY()][pos.IntX()] &= ~mapFlagNumber[7 - i];
        }
    }

    return result;
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
        case GROUND_TYPE::WETLAND:
            result = mpResourceManager->AddResource(L"Resource/mapchip.png");
            break;

        case GROUND_TYPE::SNOWFIELD:
            result = mpResourceManager->AddResource(L"Resource/Snow.png");
            break;

        case GROUND_TYPE::VOLCANIC:
            result = mpResourceManager->AddResource(L"Resource/Base.png");
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
            result = mpResourceManager->AddResource(L"Resource/mapchip.png");
            break;

        case MAP_OBJECT_TYPE::WATER_PUDDLE:
            switch ((GROUND_TYPE)((number >> 4) & 0xf))
            {
            case GROUND_TYPE::DESERT:
                break;
            case GROUND_TYPE::FOREST:
                result = mpResourceManager->AddResource(L"Resource/Map/WaterPuddle/Forest.png");
                break;
            case GROUND_TYPE::PLAIN:
                result = mpResourceManager->AddResource(L"Resource/Map/WaterPuddle/Plain.png");
                break;
            case GROUND_TYPE::SAVANNA:
                break;
            case GROUND_TYPE::SNOWFIELD:
                result = mpResourceManager->AddResource(L"Resource/Map/WaterPuddle/Ice.png");
                break;
            case GROUND_TYPE::VOLCANIC:
                result = mpResourceManager->AddResource(L"Resource/Map/WaterPuddle/Lava.png");
                break;
            case GROUND_TYPE::WETLAND:
                result = mpResourceManager->AddResource(L"Resource/Map/WaterPuddle/Wetland.png");
                break;
            }
            break;

        case MAP_OBJECT_TYPE::ROAD:
            switch ((GROUND_TYPE)((number >> 4) & 0xf))
            {
            case GROUND_TYPE::DESERT:
                result = mpResourceManager->AddResource(L"Resource/Map/Road/Desert_and_Savanna.png");
                break;
            case GROUND_TYPE::FOREST:
                result = mpResourceManager->AddResource(L"Resource/Map/Road/Forest.png");
                break;
            case GROUND_TYPE::PLAIN:
                result = mpResourceManager->AddResource(L"Resource/Map/Road/Plain.png");
                break;
            case GROUND_TYPE::SAVANNA:
                result = mpResourceManager->AddResource(L"Resource/Map/Road/Desert_and_Savanna.png");
                break;
            case GROUND_TYPE::SNOWFIELD:
                result = mpResourceManager->AddResource(L"Resource/Map/Road/Snow.png");
                break;
            case GROUND_TYPE::VOLCANIC:
                break;
            case GROUND_TYPE::WETLAND:
                result = mpResourceManager->AddResource(L"Resource/Map/Road/Wetland.png");
                break;
            }
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