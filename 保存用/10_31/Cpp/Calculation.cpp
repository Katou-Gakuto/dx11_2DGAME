#include "../Header/Calculation.h"

/// <summary>差異を減らす</summary>
void Calculation::DiffReduce(float* src, float speed)
{
	if (*src > 0.0f)
	{
		*src -= speed;
		if (*src < 0.0f)
		{
			*src = 0.0f;
		}
	}
	else
	{
		*src += speed;
		if (*src > 0.0f)
		{
			*src = 0.0f;
		}
	}
}

 
/// <summary>誤差を考慮して同じ値かを確認する</summary>
bool Calculation::ErrorEqualEqual(float src, float dst)
{
	if (src <= (dst + 0.01f))
	{
		if (src >= (dst - 0.01f))
		{
			return true;
		}
	}

	return false;
}