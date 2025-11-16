#pragma once
#include "TemplateData.h"

class Calculation
{
public:
	/*差異を減らす*/
	static void DiffReduce(float* src, float speed);

	/*誤差を考慮して同じ値かを確認する*/
	static bool ErrorEqualEqual(float src, float dst);
};