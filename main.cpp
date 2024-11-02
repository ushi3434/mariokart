// ==============================================
// main.cpp [mariokart]
// 
// �����:ushi34        ���t:2024/10/31
// ==============================================
#include <iostream>
#include <math.h>
#include "vec2.h"
#include "ushi34toolkit.h"
#include <Windows.h>
#include <conio.h>

// ==============================================
// �}�N����`
// ==============================================
#define M_PI        (3.14159265358979323846264338327950288) 

#define WINDOW_WIDTH  (60)
#define WINDOW_HEIGHT (30)

#define MAP_X (32)
#define MAP_Y (16)

#define START_X (5)
#define START_Y (5)

#define FOV_DEG (70)

// ==============================================
// �񋓌^�錾
// ==============================================
enum TILE_KEY //�o�͂���e�����̃L�[
{
	TILE_NULL = 0,
	TILE_ROAD,
	TILE_BUMPER,
	TILE_BACKGROUND,
	TILE_MAX
};

// ==============================================
// �\���̐錾
// ==============================================
struct PLAYER //�v���C���[
{
	VEC2 pos = { START_X,START_Y };
	double angle = 0;	//���W�A�� �����v��肪��
	double altitude = 0;	//���x
};

// ==============================================
// �O���[�o���錾
// ==============================================
char g_map[16][32] =
{
	{0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0},
	{0,0,0,0,0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,2,0,0,0,0,0},
	{0,0,0,0,2,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,2,0,0,0,0},
	{0,0,0,2,1,1,1,2,2,1,1,1,2,0,0,0,0,0,0,2,1,1,1,2,2,1,1,1,2,0,0,0},
	{0,0,0,2,1,1,2,0,0,2,1,1,1,2,2,2,2,2,2,1,1,1,2,0,0,2,1,1,2,0,0,0},
	{0,0,0,2,1,1,2,0,0,0,2,1,1,1,1,1,1,1,1,1,1,2,0,0,0,2,1,1,2,0,0,0},
	{0,0,0,2,1,1,2,0,0,0,0,2,1,1,1,1,1,1,1,1,2,0,0,0,0,2,1,1,2,0,0,0},
	{0,0,0,2,1,1,2,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,2,1,1,2,0,0,0},
	{0,0,0,2,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,2,0,0,0},
	{0,0,0,2,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,2,0,0,0},
	{0,0,0,2,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,2,0,0,0},
	{0,0,0,0,2,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,2,0,0,0,0},
	{0,0,0,0,0,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,0,0,0,0,0},
	{0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0},
};

PLAYER player;
char displayData[WINDOW_HEIGHT][WINDOW_WIDTH] = {};
char displayBuffer[WINDOW_HEIGHT][WINDOW_WIDTH] = {};

// ==============================================
// �v���g�^�C�v�錾
// ==============================================
void UpdateScreen(void);
void OutputChar(char);

// ==============================================
// main�֐��i�G���g���[�|�C���g�j
// ==============================================
int main(void)
{
	for (int i = 0; i < WINDOW_HEIGHT; i++)
		for (int j = 0; j < WINDOW_WIDTH; j++)
			displayData[i][j] = TILE_MAX;

	DeleteCursor();

	while (true)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'a':
				player.angle += M_PI / 180;
				break;

			case 'd':
				player.angle -= M_PI / 180;
				break;

			}
		}

		//��ʂ̍X�V
		UpdateScreen();

		//�t���[������
		Sleep(16);
	}

}

// ==============================================
// ��ʂ��X�V����֐�
// ==============================================
void UpdateScreen()
{

	static const VEC2 fovEdge = { 10,0 };

	VEC2 fovEdgeLeft;
	VEC2 fovEdgeRight;
	VEC2 Cursor;		//�e���C��world���W���w���x�N�g��

	//�v���C���[�̎���͈͂̌v�Z
	fovEdgeLeft = Vec2_Rotate(fovEdge, player.angle);
	fovEdgeRight = Vec2_Rotate(fovEdgeLeft, (-FOV_DEG * M_PI) / 180);

	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH; j++)
		{
			float horizontalPos = (float)j / WINDOW_WIDTH;
			float verticalPos = (float)i / WINDOW_HEIGHT;

			Cursor = Vec2_Add(
				Vec2_Multiply(fovEdgeLeft, verticalPos * (1 - horizontalPos)),
				Vec2_Multiply(fovEdgeRight, verticalPos * horizontalPos));

			Cursor = Vec2_Add(Cursor, player.pos);

			if (0 <= Cursor.x && Cursor.x < MAP_X + 1 && 0 <= Cursor.y && Cursor.y < MAP_Y + 1)
				//�����J�[�\�������[���h���W�̓����ɂ���Ȃ�
				displayBuffer[i][j] = g_map[(int)Cursor.y][(int)Cursor.x]; //�}�b�v�̏���buffer�ɓn��

			else
				displayBuffer[i][j] = TILE_BACKGROUND; //�͈͊O�͔w�i�œh��Ԃ�

			//�����̏o��
			if (displayData[i][j] != displayBuffer[i][j])
			{
				displayData[i][j] = displayBuffer[i][j];
				MoveCursor(i, j);
				OutputChar((TILE_KEY)displayData[i][j]);
			}
		}
	}
}

// ==============================================
// �������o�͂���֐�
// ==============================================
void OutputChar(char Key)
{
	switch (Key)
	{
	case TILE_NULL:
		std::cout << "�@";
		break;

	case TILE_ROAD:
		ChangeCharColor(255,255,255);
		std::cout << "��";
		ChangeCharColor();
		break;

	case TILE_BUMPER:
		ChangeCharColor(255, 255, 0);
		std::cout << "��";
		ChangeCharColor();
		break;

	case TILE_BACKGROUND:
		ChangeBGColor(0, 128, 255);
		std::cout << "�@";
		ChangeBGColor();
		break;
	}
}