#pragma once

struct VEC2
{
	double x;
	double y;
};

//プロトタイプ宣言
VEC2 Vec2_Rotate(VEC2 vec2, double rad);
VEC2 Vec2_Multiply(VEC2 vec2, double scale);
VEC2 Vec2_Add(VEC2 first, VEC2 second);