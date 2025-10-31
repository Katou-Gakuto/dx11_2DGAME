#pragma once
#include <cmath>
#include <string>

#include "Macro.h"
#include "Master.h"
#include "ResourceManager.h"
#include "TimeManager.h"

/*ÉäÉUÉãÉgÉfÅ[É^*/
struct Result//(ÉvÉåÉCÉÑÅ[èÛë‘Ç‡å„ÅXä‹ÇﬂÇΩÇ¢)
{
	int score;
	Result()
	: score(0)
	{
	}
};

/*ÉvÉåÉCÉÑÅ[ÉfÅ[É^*/
struct PlayerData
{
	// ëÄçÏÉLÅ[
	int keyNumber;
	// ñºëO
	std::string name;
	// ÉLÉÉÉâÉNÉ^Å[É^ÉCÉv
	int charcterType;
	// ÉäÉUÉãÉg
	Result result;

	PlayerData()
	: keyNumber(0)
	, charcterType(-1)
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
* ÅyÉxÉNÉgÉãÅzä÷òA
*/
// ÉxÉNÉgÉã float(x, y)
struct VECTOR_2D
{
public:
	float X;
	float Y;


	/*--------------------------------------------------------------------------------------------------------------
	* ílÇïœä∑ÇµÇƒï‘Ç∑
	*/
	int IntX() { return (int)this->X; }
	int IntY() { return (int)this->Y; }
	/*è¨êîì_êÿÇËéÃÇƒ*/
	VECTOR_2D SetInt2D() { return { (float)((int)this->X), (float)((int)this->Y)}; }

	/*--------------------------------------------------------------------------------------------------------------
	* ÅystaticÅzèâä˙âªÇ»Ç«Ç≈égÇ§
	*/
	static VECTOR_2D Zero() { return { 0.0f, 0.0f }; }
	static VECTOR_2D One() { return { 1.0f, 1.0f }; }
	static VECTOR_2D Minus() { return { -1.0f, -1.0f }; }
	static VECTOR_2D GetFloatVec(float x, float y) { return {x, y}; }
	static VECTOR_2D GetIntVec(int x, int y) { return {(float)x, (float)y}; }

	/*--------------------------------------------------------------------------------------------------------------
	* ÅyåvéZópÅz
	*/
	/*ê‚ëŒíl*/
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
	/*ïÑçÜéÊìæ*/
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
	/*XÇ∆YÇë´ÇµÇΩílÇï‘Ç∑*/
	float GetAddXY() { return X + Y; }
	/*ÉmÅ[É}ÉâÉCÉY*/
	VECTOR_2D GetNormalize() const
	{
		float length = sqrtf((this->X * this->X) + (this->Y * this->Y));
		return VECTOR_2D::GetFloatVec(this->X / length, this->X / length);
	}

	/*--------------------------------------------------------------------------------------------------------------
	* ÅyVECTOR_2DÅzÇ∆ÇÃââéZ
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
	* ÅyfloatÅzÇ∆ÇÃââéZ
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
	* ÅyintÅzÇ∆ÇÃââéZ
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
	* ÅyVECTOR_2DÅzÇ∆ÇÃî‰är
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
	* ÅyfloatÅzÇ∆ÇÃî‰är
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
	* ÅyintÅzÇ∆ÇÃî‰är
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
* ÅyÉXÉeÅ[É^ÉXÅzä÷òA
*/
/*ÉLÉÉÉâÉNÉ^Å[É^ÉCÉv*/
enum class CHARACTER_TYPE
{
	/*Ç»Ç¢*/
	NONE = -1,
	/*ãﬂãóó£*/
	CLOSE_RENGE,

	MAX,
};

/*ÉXÉeÅ[É^ÉX*/
struct STATUS
{
private:
	// MAX_HP
	unsigned int LevelOneMaxHp;

	// çUåÇóÕ
	unsigned int LevelOneAttackPower;

public:
	// ÉåÉxÉã
	unsigned int Level;
	
	// MAX_HP
	unsigned int MaxHp;
	// HP
	int Hp;

	// çUåÇóÕ
	unsigned int AttackPower;

	// ë¨ìx
	float Speed;

	// É|ÉWÉVÉáÉì
	VECTOR_2D Position;
	
	// ÉTÉCÉY
	VECTOR_2D Size;

	// éÌóﬁ
	CHARACTER_TYPE CharacterType;

	// ÉXÉRÉA
	int Score;

	/*èâä˙âªÉfÅ[É^*/
	static STATUS InitData()
	{
		return STATUS::SetAllStatus(0, 0, 0, 0, 0.0f, VECTOR_2D::Zero(), VECTOR_2D::Zero(), CHARACTER_TYPE::NONE);
	}

	/*ëSÉfÅ[É^ê›íË*/
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

		return result;
	}

	/*ê›íËÇ≥ÇÍÇƒÇ¢ÇÈÉåÉxÉãÇ…è]Ç¡ÇƒÉXÉeÅ[É^ÉXÇè„Ç∞ÇÈ*/
	void SetLevelStatus(bool playerFlag)
	{
	}

	/*É_ÉÅÅ[ÉW*/
	void Damege(int damege)
	{
		this->Hp -= damege;
		if (this->Hp < 0)
		{
			this->Hp = 0;
		}
	}

	/*HPÇ™0à»â∫Ç…Ç»Ç¡ÇƒÇ¢Ç»Ç¢Ç©ämîFÇ∑ÇÈ*/
	bool HpCheck() const
	{
		if (this->Hp <= 0)
		{
			return true;
		}
		return false;
	}

	/*âÒïú*/
	void Recovery(int recovery)
	{
		this->Hp += recovery;
		if (this->Hp > (int)MaxHp)
		{
			this->Hp = MaxHp;
		}
	}

	/*ÉXÉRÉAëùâ¡*/
	void PlusScore(int score)
	{
		this->Score = score;
	}
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* ÅyìñÇΩÇËîªíËèÓïÒÅzä÷òA
*/
/*ìñÇΩÇËîªíËÇÃéÌóﬁ*/
enum class COLLISION_TYPE
{
	NONE = 0,
	BOX,
	PLAYER,
	ENEMY,
};

/*ìñÇΩÇËîªíËèÓïÒ*/
struct CollisionData
{
public:
	// É|ÉWÉVÉáÉì
	VECTOR_2D Position;
	
	// ëOÇÃÉ|ÉWÉVÉáÉì
	VECTOR_2D OldPosition;

	// ÉTÉCÉY
	VECTOR_2D Size;
	
	// ìñÇΩÇÁÇÕÇ¢Ç∆Ç±ÇÎÇ‹Ç≈ÇÃà⁄ìÆó 
	VECTOR_2D NotHitPosMove;
	
	// ìñÇΩÇËîªíËÇÃéÌóﬁ
	COLLISION_TYPE CollisionType;
	
	// ìñÇΩÇ¡ÇΩêî
	int HitCount;

	COLLISION_TYPE ObjectType;

	/*èâä˙âªÉfÅ[É^*/
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

	/*à⁄ìÆó */
	VECTOR_2D MoveVec()	{ return this->Position - this->OldPosition; }

	/*â∫ç¿ïW*/
	float GetDownPos() { return this->Position.Y + (this->Size.Y * 0.5f); }
	/*è„ç¿ïW*/
	float GetUpPos() { return this->Position.Y - (this->Size.Y * 0.5f); }
	/*âEç¿ïW*/
	float GetRightPos() { return this->Position.X + (this->Size.X * 0.5f); }
	/*ç∂ç¿ïW*/
	float GetLeftPos() { return this->Position.X - (this->Size.X * 0.5f); }
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* Åyï`âÊÅzä÷òA
*/
/*ï`âÊéÌóﬁ*/
enum class DRAW_TYPE
{
	/*Ç»Ç¢*/
	NONE = 0,
	/*ÉãÅ[ÉvXé≤Iå^çƒê∂*/
	LOOP_X_AXIS_I_DRAW,
	/*ÉãÅ[ÉvXé≤Iå^âùïúçƒê∂*/
	LOOP_X_AXIS_I_RETURN_DRAW,
	/*1çƒê∂Xé≤Iå^çƒê∂*/
	ONE_X_AXIS_I_DRAW,	
	/*í‚é~çƒê∂*/
	STOP_DRAW,
};

/*ï`âÊèÓïÒ*/
struct DrawData
{
	// ï`âÊéÌóﬁ
	DRAW_TYPE drawType;

	// ï`âÊç≈è¨UVíl
	VECTOR_2D minDrawUVPos;
	// ï`âÊç≈ëÂUVíl
	VECTOR_2D maxDrawUVPos;
	// åªç›ï`âÊUVíl
	VECTOR_2D nowDrawUVPos;
	// ï`âÊUVÉTÉCÉY
	VECTOR_2D UVSize;
	// ï`âÊà⁄ìÆ
	VECTOR_2D drawUVMoveVolume;

	// í‚é~éûï`âÊï`âÊâ”èä
	VECTOR_2D stopDrawPos;

	// ï`âÊÉ|ÉWÉVÉáÉì
	VECTOR_2D drawPos;
	// ï`âÊÉTÉCÉY
	VECTOR_2D drawSize;

	// ëOÇÃäGÇÃï`âÊäJénéûä‘
	int oldDrawTime;
	// 1ñáÇÃï`âÊéûä‘
	int oneDrawTime;
	
	// ÉäÉ\Å[ÉXID
	int resourceId;

	// ï`âÊintÉtÉâÉO
	int drawIntFlag;

	// äGÇÃñáêî(Xé≤)
	int resourceXNumber;
	// äGÇÃñáêî(Yé≤)
	int resourceYNumber;

	// ï`âÊçXêVèIóπÉtÉâÉO
	bool drawEndFlag;

	/*--------------------------------------------------------------------------------------------------------------
	* ÅystaticÅz
	*/
	/*èâä˙âªÉfÅ[É^*/
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
	* Åyï`âÊä÷òAèàóùÅz
	*/
	/*ï`âÊèÓïÒê›íË*/
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

	/*ï`âÊçXêV*/
	void DrawUpdate(int setDrawNumber)
	{
		if (setDrawNumber != -1)
		{
			/*--------------------------------------------------------------------------------------------------------------
			* ÅyXé≤ï`âÊèàóùÅz
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
			* ÅyYé≤ï`âÊèàóùÅz
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
		* Åyí‚é~éûèàóùÅz
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

	/*ï`âÊ*/
	void Draw()
	{
		Master::mpResourceManager->DrawSprite(drawPos.X, drawPos.Y, drawSize.X, drawSize.Y, nowDrawUVPos.X, UVSize.X, nowDrawUVPos.Y, UVSize.Y, resourceId, drawIntFlag);
	}
};