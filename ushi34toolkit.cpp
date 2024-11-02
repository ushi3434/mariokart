#include "ushi34toolkit.h"
#include <iostream>
#include <Windows.h>

// ==============================================
// カーソルを移動させる関数
// ==============================================
void MoveCursor(int Y, int X)
{
	//出力を全角文字で統一しているので、Xは2倍にする
	std::cout << "\033[" << Y + 1 << ";" << 2 * X + 1 << "H";
}

// ==============================================
// カーソルを非表示にする関数
// ==============================================
void DeleteCursor(void)
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO cci;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleCursorInfo(hOut, &cci);

	cci.bVisible = FALSE;

	SetConsoleCursorInfo(hOut, &cci);
}

// ==============================================
// 出力する文字の色をRGBで指定する関数
// ==============================================
void ChangeCharColor(int r, int g, int b)
{
	std::cout << "\x1b[38;2;" << r << ";" << g << ";" << b << "m";
}

//色リセット
void ChangeCharColor(void)
{
	std::cout << "\x1b[39m";
}

// ==============================================
// 出力する背景の色をRGBで指定する関数
// ==============================================
void ChangeBGColor(int r, int g, int b)
{
	std::cout << "\x1b[48;2;" << r << ";" << g << ";" << b << "m";
}

//色リセット
void ChangeBGColor(void)
{
	std::cout << "\x1b[49m";
}