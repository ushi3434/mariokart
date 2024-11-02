#include <math.h>
#include "vec2.h"

// ==============================================
// �x�N�g���̉�]���s���֐�
// �߂�l�F���Z����
// ==============================================
VEC2 Vec2_Rotate(VEC2 vec2, double rad)
{
	VEC2 temp;

	temp.x = vec2.x * cos(rad) - vec2.y * sin(rad);
	temp.y = vec2.x * sin(rad) + vec2.y * cos(rad);

	return temp;
}

// ==============================================
// �x�N�g���̊|���Z���s���֐�
// �߂�l�F���Z����
// ==============================================
VEC2 Vec2_Multiply(VEC2 vec2, double scale)
{
	VEC2 temp;

	temp.x = vec2.x * scale;
	temp.y = vec2.y * scale;

	return temp;
}

// ==============================================
// �x�N�g���̑����Z���s���֐�
// �߂�l�F���Z����
// ==============================================
VEC2 Vec2_Add(VEC2 first, VEC2 second)
{
	VEC2 temp;

	temp.x = first.x + second.x;
	temp.y = first.y + second.y;

	return temp;
}