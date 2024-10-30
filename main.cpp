#include <iostream>
#include <math.h>

#define M_PI        (3.14159265358979323846264338327950288) 

#define WINDOW_WIDTH  (60)
#define WINDOW_HEIGHT (30)

struct VEC2
{
	float x;
	float y;
};

//プロトタイプ宣言
void rotateVec2(VEC2&, float);


int main(void)
{

}

void rotateVec2(VEC2& vec2,float rad)
{
	VEC2 temp = vec2;

	vec2.x = temp.x * cos(rad) - temp.y * sin(rad);
	vec2.y = temp.x * sin(rad) + temp.y * cos(rad);
}