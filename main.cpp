// ==============================================
// main.cpp [mariokart]
// 
// 制作者:ushi34        日付:2024/10/31
// ==============================================
#include <iostream>
#include <math.h>
#include "vec2.h"
#include "ushi34toolkit.h"
#include <Windows.h>
#include <conio.h>

// ==============================================
// マクロ定義
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
// 列挙型宣言
// ==============================================
enum TILE_KEY //出力する各文字のキー
{
	TILE_NULL = 0,
	TILE_ROAD,
	TILE_BUMPER,
	TILE_BACKGROUND,
	TILE_MAX
};

// ==============================================
// 構造体宣言
// ==============================================
struct PLAYER //プレイヤー
{
	VEC2 pos = { START_X,START_Y };
	double angle = 0;	//ラジアン 反時計回りが正
	double altitude = 0;	//高度
};

// ==============================================
// グローバル宣言
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
// プロトタイプ宣言
// ==============================================
void UpdateScreen(void);
void OutputChar(char);

// ==============================================
// main関数（エントリーポイント）
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

		//画面の更新
		UpdateScreen();

		//フレーム調整
		Sleep(16);
	}

}

// ==============================================
// 画面を更新する関数
// ==============================================
void UpdateScreen()
{

	static const VEC2 fovEdge = { 10,0 };

	VEC2 fovEdgeLeft;
	VEC2 fovEdgeRight;
	VEC2 Cursor;		//各レイのworld座標を指すベクトル

	//プレイヤーの視野範囲の計算
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
				//もしカーソルがワールド座標の内部にあるなら
				displayBuffer[i][j] = g_map[(int)Cursor.y][(int)Cursor.x]; //マップの情報をbufferに渡す

			else
				displayBuffer[i][j] = TILE_BACKGROUND; //範囲外は背景で塗りつぶす

			//文字の出力
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
// 文字を出力する関数
// ==============================================
void OutputChar(char Key)
{
	switch (Key)
	{
	case TILE_NULL:
		std::cout << "　";
		break;

	case TILE_ROAD:
		ChangeCharColor(255,255,255);
		std::cout << "■";
		ChangeCharColor();
		break;

	case TILE_BUMPER:
		ChangeCharColor(255, 255, 0);
		std::cout << "■";
		ChangeCharColor();
		break;

	case TILE_BACKGROUND:
		ChangeBGColor(0, 128, 255);
		std::cout << "　";
		ChangeBGColor();
		break;
	}
}