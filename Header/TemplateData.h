#pragma once
#include <cmath>
#include <string>

#include "Macro.h"
#include "Master.h"
#include "ResourceManager.h"
#include "TimeManager.h"

/*リザルトデータ*/
struct Result//(プレイヤー状態も後々含めたい)
{
	int score;
	int damegeCount;
	Result()
	: score(0)
	, damegeCount(0)
	{
	}
};

/*プレイヤーデータ*/
struct PlayerData
{
	// 操作キー
	int keyNumber;
	// 名前
	std::string name;
	// キャラクタータイプ
	int characterType;
	// リザルト
	Result result;

	PlayerData()
	: keyNumber(-1)
	, characterType(-1)
	, result(Result())
	{
		name.clear();
	}

	int* GetKeyNumber()
	{
		return &keyNumber;
	}
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【ベクトル】関連
*/
// ベクトル float(x, y)
struct VECTOR_2D
{
public:
	float X;
	float Y;


	/*--------------------------------------------------------------------------------------------------------------
	* 値を変換して返す
	*/
	int IntX() { return (int)this->X; }
	int IntY() { return (int)this->Y; }
	/*小数点切り捨て*/
	VECTOR_2D SetInt2D() { return { (float)((int)this->X), (float)((int)this->Y)}; }

	/*--------------------------------------------------------------------------------------------------------------
	* 【static】初期化などで使う
	*/
	static VECTOR_2D Zero() { return { 0.0f, 0.0f }; }
	static VECTOR_2D One() { return { 1.0f, 1.0f }; }
	static VECTOR_2D Minus() { return { -1.0f, -1.0f }; }
	static VECTOR_2D GetFloatVec(float x, float y) { return {x, y}; }
	static VECTOR_2D GetIntVec(int x, int y) { return {(float)x, (float)y}; }

	/*--------------------------------------------------------------------------------------------------------------
	* 【計算用】
	*/
	/*絶対値*/
	VECTOR_2D Abs()
	{
		VECTOR_2D abs;

		if (this->X >= 0.0f)
		{
			abs.X = this->X;
		}
		else if (this->X < 0.0f)
		{
			abs.X = -this->X;
		}

		if (this->Y >= 0.0f)
		{
			abs.Y = this->Y;
		}
		else if (this->Y < 0.0f)
		{
			abs.Y = -this->Y;
		}

		return abs;
	}
	/*符号取得*/
	VECTOR_2D Sign()
	{

		VECTOR_2D sign;

		if (this->X >= 0.0f)
		{
			sign.X = 1;
		}
		else if (this->X < 0.0f)
		{
			sign.X = -1;
		}

		if (this->Y >= 0.0f)
		{
			sign.Y = 1;
		}
		else if (this->Y < 0.0f)
		{
			sign.Y = -1;
		}

		return sign;
	}
	/*XとYを足した値を返す*/
	float GetAddXY() { return X + Y; }
	/*ノーマライズ*/
	VECTOR_2D GetNormalize() const
	{
		float length = sqrtf((this->X * this->X) + (this->Y * this->Y));
		return VECTOR_2D::GetFloatVec(this->X / length, this->X / length);
	}

	/*--------------------------------------------------------------------------------------------------------------
	* 【VECTOR_2D】との演算
	*/
	VECTOR_2D operator +(VECTOR_2D other) const
	{
		return { this->X + other.X, this->Y + other.Y };
	}
	VECTOR_2D operator -(VECTOR_2D other) const
	{
		return { this->X - other.X, this->Y - other.Y };
	}
	VECTOR_2D operator /(VECTOR_2D other) const
	{
		return { this->X / other.X, this->Y / other.Y };
	}
	VECTOR_2D operator *(VECTOR_2D other) const
	{
		return { this->X * other.X, this->Y * other.Y };
	}

	VECTOR_2D& operator =(VECTOR_2D other)
	{
		this->X = other.X;
		this->Y = other.Y;
		return *this;
	}
	VECTOR_2D& operator +=(VECTOR_2D other)
	{
		return *this = (*this + other);
	}
	VECTOR_2D& operator -=(VECTOR_2D other)
	{
		return *this = (*this - other);
	}
	VECTOR_2D& operator /=(VECTOR_2D other)
	{
		return *this = (*this + other);
	}
	VECTOR_2D& operator *=(VECTOR_2D other)
	{
		return *this = (*this * other);
	}

	/*--------------------------------------------------------------------------------------------------------------
	* 【float】との演算
	*/
	VECTOR_2D operator +(float other) const
	{
		return { this->X + other, this->Y + other };
	}
	VECTOR_2D operator -(float other) const
	{
		return { this->X - other, this->Y - other };
	}
	VECTOR_2D operator /(float other) const
	{
		return { this->X / other, this->Y / other };
	}
	VECTOR_2D operator *(float other) const
	{
		return { this->X * other, this->Y * other };
	}

	VECTOR_2D& operator =(float other)
	{
		return *this ={other , other};
	}
	VECTOR_2D& operator +=(float other)
	{
		return *this = (*this + other);
	}
	VECTOR_2D& operator -=(float other)
	{
		return *this = (*this - other);
	}
	VECTOR_2D& operator /=(float other)
	{
		return *this = (*this / other);
	}
	VECTOR_2D& operator *=(float other)
	{
		return *this = (*this * other);
	}

	/*--------------------------------------------------------------------------------------------------------------
	* 【int】との演算
	*/
	VECTOR_2D operator +(int other) const
	{
		return *this + (float)other;
	}
	VECTOR_2D operator -(int other) const
	{
		return *this - (float)other;
	}
	VECTOR_2D operator /(int other) const
	{
		return *this / (float)other;
	}
	VECTOR_2D operator *(int other) const
	{
		return *this * (float)other;
	}

	VECTOR_2D& operator =(int other)
	{
		return *this = (float)other;
	}
	VECTOR_2D& operator +=(int other)
	{
		return *this = (*this + other);
	}
	VECTOR_2D& operator -=(int other)
	{
		return *this = (*this - other);
	}
	VECTOR_2D& operator /=(int other)
	{
		return *this = (*this / other);
	}
	VECTOR_2D& operator *=(int other)
	{
		return *this = (*this * other);
	}

	/*--------------------------------------------------------------------------------------------------------------
	* 【VECTOR_2D】との比較
	*/
	bool operator ==(VECTOR_2D other) const
	{
		return (this->X == other.X) && (this->Y == other.Y);
	}
	bool operator !=(VECTOR_2D other) const
	{
		return (this->X != other.X) || (this->Y != other.Y);
	}

	bool operator <(VECTOR_2D other) const
	{
		return (this->X < other.X) && (this->Y < other.Y);
	}
	bool operator <=(VECTOR_2D other) const
	{
		return (this->X <= other.X) && (this->Y <= other.Y);
	}
	bool operator >(VECTOR_2D other) const
	{
		return (this->X > other.X) && (this->Y > other.Y);
	}
	bool operator >=(VECTOR_2D other) const
	{
		return (this->X >= other.X) && (this->Y >= other.Y);
	}

	/*--------------------------------------------------------------------------------------------------------------
	* 【float】との比較
	*/
	bool operator ==(float other) const
	{
		return (this->X == other) && (this->Y == other);
	}
	bool operator !=(float other) const
	{
		return (this->X != other) || (this->Y != other);
	}

	bool operator <(float other) const
	{
		return (this->X < other) && (this->Y < other);
	}
	bool operator <=(float other) const
	{
		return (this->X <= other) && (this->Y <= other);
	}
	bool operator >(float other) const
	{
		return (this->X > other) && (this->Y > other);
	}
	bool operator >=(float other) const
	{
		return (this->X >= other) && (this->Y >= other);
	}

	/*--------------------------------------------------------------------------------------------------------------
	* 【int】との比較
	*/
	bool operator ==(int other) const
	{
		return *this == (float)other;
	}
	bool operator !=(int other) const
	{
		return *this != (float)other;
	}

	bool operator <(int other) const
	{
		return *this < (float)other;
	}
	bool operator <=(int other) const
	{
		return *this <= (float)other;
	}
	bool operator >(int other) const
	{
		return *this > (float)other;
	}
	bool operator >=(int other) const
	{
		return *this >= (float)other;
	}
};


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【ステータス】関連
*/
/*キャラクタータイプ*/
enum class CHARACTER_TYPE
{
	/*ない*/
	NONE = -1,
	/*近距離*/
	CLOSE_RENGE,

	MAX,
};

/*ステータス*/
struct STATUS
{
private:
	// MAX_HP
	unsigned int LevelOneMaxHp;

	// 攻撃力
	unsigned int LevelOneAttackPower;

	// 前回のダメージを受けた時間
	int PreDamegeTime;

	// 無敵時間
	int InvincibilityTime;

public:
	// レベル
	unsigned int Level;
	
	// MAX_HP
	unsigned int MaxHp;
	// HP
	int Hp;

	// 攻撃力
	unsigned int AttackPower;

	// 速度
	float Speed;

	// ポジション
	VECTOR_2D Position;
	
	// サイズ
	VECTOR_2D Size;

	// 種類
	CHARACTER_TYPE CharacterType;

	// スコア
	int Score;

	/*初期化データ*/
	static STATUS InitData()
	{
		return STATUS::SetAllStatus(0, 0, 0, 0, 0.0f, VECTOR_2D::Zero(), VECTOR_2D::Zero(), CHARACTER_TYPE::NONE);
	}

	/*全データ設定*/
	static STATUS SetAllStatus(unsigned int level, unsigned int maxHp, int hp, unsigned int attackPower, float speed, VECTOR_2D position, VECTOR_2D size, CHARACTER_TYPE characterType)
	{
		STATUS result = STATUS();
		result.Level = level;
		result.MaxHp = maxHp;
		result.LevelOneMaxHp = maxHp;
		result.Hp = hp;
		result.AttackPower = attackPower;
		result.LevelOneAttackPower = attackPower;
		result.Speed = speed;
		result.Position = position;
		result.Size = size;
		result.CharacterType = characterType;
		result.Score = 0;
		result.PreDamegeTime = 0;
		result.InvincibilityTime = 340;

		return result;
	}

	/*設定されているレベルに従ってステータスを上げる*/
	void SetLevelStatus(bool playerFlag)
	{
	}

	/*ダメージ*/
	void Damege(int damege)
	{
		if ((PreDamegeTime + InvincibilityTime) <= Master::mpTimeManager->GetGameTime())
		{
			PreDamegeTime = Master::mpTimeManager->GetGameTime();
			this->Hp -= damege;
			if (this->Hp < 0)
			{
				this->Hp = 0;
			}
		}
	}

	/*HPが0以下になっていないか確認する*/
	bool HpCheck() const
	{
		if (this->Hp <= 0)
		{
			return true;
		}
		return false;
	}

	/*回復*/
	void Recovery(int recovery)
	{
		this->Hp += recovery;
		if (this->Hp > (int)MaxHp)
		{
			this->Hp = MaxHp;
		}
	}

	/*スコア増加*/
	void PlusScore(int score)
	{
		this->Score += score;
	}
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【当たり判定情報】関連
*/
/*当たり判定の種類*/
enum class COLLISION_TYPE
{
	NONE = 0,
	BOX,
	PLAYER,
	ENEMY,
};

/*当たり判定情報*/
struct CollisionData
{
public:
	// ポジション
	VECTOR_2D Position;
	
	// 前のポジション
	VECTOR_2D OldPosition;

	// サイズ
	VECTOR_2D Size;
	
	// 当たらはいところまでの移動量
	VECTOR_2D NotHitPosMove;
	
	// 当たり判定の種類
	COLLISION_TYPE CollisionType;
	
	// 当たった数
	int HitCount;

	COLLISION_TYPE ObjectType;

	/*初期化データ*/
	static CollisionData InitData()
	{
		CollisionData initData = CollisionData();
		initData.Position = VECTOR_2D::Zero();
		initData.OldPosition = VECTOR_2D::Zero();
		initData.Size = VECTOR_2D::Zero();
		initData.NotHitPosMove = VECTOR_2D::Zero();
		initData.CollisionType = COLLISION_TYPE::NONE;
		initData.HitCount = 0;
		initData.ObjectType = COLLISION_TYPE::NONE;

		return initData;
	}

	/*移動量*/
	VECTOR_2D MoveVec()	{ return this->Position - this->OldPosition; }

	/*下座標*/
	float GetDownPos() { return this->Position.Y + (this->Size.Y * 0.5f); }
	/*上座標*/
	float GetUpPos() { return this->Position.Y - (this->Size.Y * 0.5f); }
	/*右座標*/
	float GetRightPos() { return this->Position.X + (this->Size.X * 0.5f); }
	/*左座標*/
	float GetLeftPos() { return this->Position.X - (this->Size.X * 0.5f); }
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【描画】関連
*/
/*描画種類*/
enum class DRAW_TYPE
{
	/*ない*/
	NONE = 0,
	/*ループX軸I型再生*/
	LOOP_X_AXIS_I_DRAW,
	/*ループX軸I型往復再生*/
	LOOP_X_AXIS_I_RETURN_DRAW,
	/*1再生X軸I型再生*/
	ONE_X_AXIS_I_DRAW,	
	/*停止再生*/
	STOP_DRAW,
};

/*描画情報*/
struct DrawData
{
	// 描画種類
	DRAW_TYPE drawType;

	// 描画最小UV値
	VECTOR_2D minDrawUVPos;
	// 描画最大UV値
	VECTOR_2D maxDrawUVPos;
	// 現在描画UV値
	VECTOR_2D nowDrawUVPos;
	// 描画UVサイズ
	VECTOR_2D UVSize;
	// 描画移動
	VECTOR_2D drawUVMoveVolume;

	// 停止時描画描画箇所
	VECTOR_2D stopDrawPos;

	// 描画ポジション
	VECTOR_2D drawPos;
	// 描画サイズ
	VECTOR_2D drawSize;

	// 前の絵の描画開始時間
	int oldDrawTime;
	// 1枚の描画時間
	int oneDrawTime;
	
	// リソースID
	int resourceId;

	// 描画intフラグ
	int drawIntFlag;

	// 絵の枚数(X軸)
	int resourceXNumber;
	// 絵の枚数(Y軸)
	int resourceYNumber;

	// 描画更新終了フラグ
	bool drawEndFlag;

	/*--------------------------------------------------------------------------------------------------------------
	* 【static】
	*/
	/*初期化データ*/
	static DrawData InitData()
	{
		DrawData initData = DrawData();
		initData.drawType = DRAW_TYPE::NONE;
		initData.minDrawUVPos = VECTOR_2D::Zero();
		initData.maxDrawUVPos = VECTOR_2D::Zero();
		initData.nowDrawUVPos = VECTOR_2D::Zero();
		initData.UVSize = VECTOR_2D::Zero();
		initData.drawUVMoveVolume = VECTOR_2D::Zero();
		initData.stopDrawPos = VECTOR_2D::Minus();
		initData.drawPos = VECTOR_2D::Zero();
		initData.drawSize = VECTOR_2D::Zero();
		initData.oldDrawTime = 0;
		initData.oneDrawTime = 0;
		initData.resourceId = -1;
		initData.drawIntFlag = 0;
		initData.resourceXNumber = 0;
		initData.resourceYNumber = 0;
		initData.drawEndFlag = false;

		return initData;
	}


	/*--------------------------------------------------------------------------------------------------------------
	* 【描画関連処理】
	*/
	/*描画情報設定*/
	void SetDrawData(DRAW_TYPE setDrawType, VECTOR_2D setMinUV, VECTOR_2D setMaxUV, VECTOR_2D setNowUV, VECTOR_2D setStopDrawPos, VECTOR_2D setDrawPos, VECTOR_2D setDrawSize, int setOneDrawTime, int setResourceId, int setDrawIntFlag, int setResourceXNumber, int setResourceYNumber)
	{
		drawType = setDrawType;
		minDrawUVPos = setMinUV;
		maxDrawUVPos = setMaxUV;
		nowDrawUVPos = setNowUV;
		stopDrawPos = setStopDrawPos;
		drawPos = setDrawPos;
		drawSize = setDrawSize;
		oldDrawTime = Master::mpTimeManager->GetGameTime();
		oneDrawTime = setOneDrawTime;
		resourceId = setResourceId;
		drawIntFlag = setDrawIntFlag;
		resourceXNumber = setResourceXNumber;
		resourceYNumber = setResourceYNumber;
		drawEndFlag = false;

		UVSize = VECTOR_2D::GetFloatVec(1.0f / (float)setResourceXNumber, 1.0f / (float)setResourceYNumber);
		drawUVMoveVolume = UVSize;
	}

	static DrawData GetDrawData(int number, const wchar_t* fileName)
	{
		DrawData result = DrawData::InitData();
		switch (number)
		{
		case 0:
			result.SetDrawData(DRAW_TYPE::LOOP_X_AXIS_I_RETURN_DRAW, VECTOR_2D::Zero(), VECTOR_2D::GetFloatVec(1.0f, 0.25f), VECTOR_2D::GetFloatVec(1.0f / 3.0f, 0.0f), VECTOR_2D::GetFloatVec(1.0f / 3.0f, -1.0f), VECTOR_2D::Zero(), VECTOR_2D::One(), 300, Master::mpResourceManager->AddResource(/*L"Resource/pipo-charachip001.png"*/fileName), MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG, 3, 4);
			break;

		case 1:
			result.SetDrawData(DRAW_TYPE::ONE_X_AXIS_I_DRAW, VECTOR_2D::Zero(), VECTOR_2D::One(), VECTOR_2D::GetFloatVec(0.0f, 0.0f), VECTOR_2D::GetFloatVec(1.0f / 3.0f, -1.0f), VECTOR_2D::Zero(), VECTOR_2D::One(), 50, Master::mpResourceManager->AddResource(/*L"Resource/pipo-charachip001.png"*/fileName), MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG | CAMERA_VIEW_FLAG, 9, 1);
			break;
		}

		return result;
	}

	/*描画更新*/
	void DrawUpdate(int setDrawNumber)
	{
		if (setDrawNumber != -1)
		{
			/*--------------------------------------------------------------------------------------------------------------
			* 【X軸描画処理】
			*/
			if ((nowDrawUVPos.Y >= ((setDrawNumber * UVSize.Y) - 0.001f)) &&
			    (nowDrawUVPos.Y <= ((setDrawNumber * UVSize.Y) + 0.001f)))
			{
				if (Master::mpTimeManager->GetGameTime() > (oldDrawTime + oneDrawTime))
				{
					switch (drawType)
					{
					case DRAW_TYPE::LOOP_X_AXIS_I_DRAW:
						nowDrawUVPos.X += drawUVMoveVolume.X;
						oldDrawTime = Master::mpTimeManager->GetGameTime();

						if ((nowDrawUVPos.X + drawUVMoveVolume.X) > maxDrawUVPos.X)
						{
							nowDrawUVPos.X = minDrawUVPos.X;
						}
						break;

					case DRAW_TYPE::LOOP_X_AXIS_I_RETURN_DRAW:
						nowDrawUVPos.X += drawUVMoveVolume.X;
						oldDrawTime = Master::mpTimeManager->GetGameTime();

						if ((nowDrawUVPos.X + drawUVMoveVolume.X) > maxDrawUVPos.X)
						{
							drawUVMoveVolume.X = -drawUVMoveVolume.X;
						}

						if (((nowDrawUVPos.X + drawUVMoveVolume.X) + 0.001f) < minDrawUVPos.X)
						{
							drawUVMoveVolume.X = -drawUVMoveVolume.X;

						}
						break;

					case DRAW_TYPE::ONE_X_AXIS_I_DRAW:
						oldDrawTime = Master::mpTimeManager->GetGameTime();
						if ((nowDrawUVPos.X + drawUVMoveVolume.X) >= maxDrawUVPos.X)
						{
							drawEndFlag = true;
							break;
						}
						nowDrawUVPos.X += drawUVMoveVolume.X;
						break;
					}
				}
			}
			else
			{
				switch (drawType)
				{
				case DRAW_TYPE::LOOP_X_AXIS_I_DRAW:
				case DRAW_TYPE::LOOP_X_AXIS_I_RETURN_DRAW:
				case DRAW_TYPE::ONE_X_AXIS_I_DRAW:

					drawUVMoveVolume = drawUVMoveVolume.Abs();
					nowDrawUVPos.Y = ((float)setDrawNumber * UVSize.Y);
					nowDrawUVPos.X = stopDrawPos.X;
					oldDrawTime = Master::mpTimeManager->GetGameTime();
					break;
				}
			}

			/*--------------------------------------------------------------------------------------------------------------
			* 【Y軸描画処理】
			*/
			if ((nowDrawUVPos.X >= ((setDrawNumber * UVSize.X) - 0.001f)) &&
				(nowDrawUVPos.X <= ((setDrawNumber * UVSize.X) + 0.001f)))
			{
				if (Master::mpTimeManager->GetGameTime() > (oldDrawTime + oneDrawTime))
				{
				}
			}
			else
			{

			}
		
		}
		/*--------------------------------------------------------------------------------------------------------------
		* 【停止時処理】
		*/
		else
		{
			if (nowDrawUVPos.IntX() != (float)- 1)
			{
				nowDrawUVPos.X = stopDrawPos.X;
			}
			else if (nowDrawUVPos.IntY() != (float)-1)
			{

			}
			drawUVMoveVolume = drawUVMoveVolume.Abs();
		}
	}

	/*描画*/
	void Draw()
	{
		Master::mpResourceManager->DrawSprite(drawPos.X, drawPos.Y, drawSize.X, drawSize.Y, nowDrawUVPos.X, UVSize.X, nowDrawUVPos.Y, UVSize.Y, resourceId, drawIntFlag);
	}
};