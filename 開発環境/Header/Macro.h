#pragma once

// 座標を中心に画像を描画する
#define MIDDLE_FLAG           0b0001
// UV値の左上座標を基準に右と下の量描画する
#define ULTRAVIOLET_PLUS_FLAG 0b0010
// カメラが見ている座標を中心にカメラの描画サイズに合わせて描画する描画する(1.0f = MAP_ONE_SQUARE_SIZE)
#define CAMERA_VIEW_FLAG 0b0100

// 1マスの大きさ
#define MAP_ONE_SQUARE_SIZE 64.0f

// マップの縦幅
#define MAP_HEIGHT_MAX (36 + 2)
// マップの横幅
#define MAP_WIDTH_MAX (60 + 2)