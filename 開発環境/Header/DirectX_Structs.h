#pragma once
#include <DirectXMath.h>

struct SimpleVertex // 頂点のフォーマット
{
	DirectX::XMFLOAT3 Pos;   // 座標
	DirectX::XMFLOAT2 Tex;   // UV値
};

// CB(コンスタントバッファー)
// ↓
// constant buffer (定数バッファ)　シェーダーとのやり取りに使用する
// 絵を書くとき必要
struct CBNeverChanges
{
    DirectX::XMMATRIX mView; // ②ビューマトリクス ビュー変換を行うための行列  /*カメラの動きに合わせて世界をカメラの反対方向に動かす*/
};

struct CBChangeOnResize
{
    DirectX::XMMATRIX mProjection;   // ③プロジェクションマトリクス プロジェクション変換を行うための行列  /*見える範囲につぶす*/
};

struct CBChangesEveryFrame
{
    DirectX::XMMATRIX mWorld;    // ①ワールドマトリクス ワールド変換を行うための行列     頂点,基本00,動きたくない  ワールド変換(原点に集まったものをちりばめる)　　/*例　プレイヤーを座標に設置*/
    DirectX::XMFLOAT4 vMeshColor;    // マテリアルデータ (材料)データ 昔と変わってるため少し違う   リフーズデータ　かくさんほう(目で見て感じる色)
};