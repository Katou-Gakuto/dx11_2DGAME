#pragma once
#include "ObjectBases.h"
#include "TemplateData.h"

class Camera;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【当たり判定関数】
*/
class CollisionFunctions
{
public:
    /*サイドの辺の中同士が当たってるかを確認する*/
    static bool SideCheck(float srcPos, float srcSize, float dstPos, float dstSize);

    /*ボックス当たり判定*/
    static bool HitBox(VECTOR_2D srcPos, VECTOR_2D srcSize, VECTOR_2D dstPos, VECTOR_2D dstSize);
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【カメラ外抑止当たり判定】
*/
class CameraCollision : public CollisionBase
{
private:
	Camera* mpCamera;

public:
    /*コンストラクタ*/
	CameraCollision();
    /*デストラクタ*/
	~CameraCollision();

    /*当たり判定*/
    virtual CollisionData CollisionCheck(CollisionData collisionData) override;

protected:
    /*コリジョン初期化*/
    virtual void CollisionInitilize() override;
    /*コリジョン終了*/
    virtual void CollisionFinalize() override;
    /*コリジョン更新*/
    virtual void CollisionUpdate() override;
    /*コリジョン描画*/
    virtual void CollisionDraw() override;
};
//
///*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//* 【カメラ外抑止当たり判定】
//*/
//class CameraCollision : public CollisionBase
//{
//
//public:
//    /*コンストラクタ*/
//	CameraCollision();
//    /*デストラクタ*/
//	~CameraCollision();
//
//    /*当たり判定*/
//    virtual CollisionData CollisionCheck(CollisionData collisionData) override;
//
//protected:
//    /*コリジョン初期化*/
//    virtual void CollisionInitilize() override;
//    /*コリジョン終了*/
//    virtual void CollisionFinalize() override;
//    /*コリジョン更新*/
//    virtual void CollisionUpdate() override;
//    /*コリジョン描画*/
//    virtual void CollisionDraw() override;
//};