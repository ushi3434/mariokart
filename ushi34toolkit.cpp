#include "ushi34toolkit.h"
#include <iostream>
#include <Windows.h>

// ==============================================
// �J�[�\�����ړ�������֐�
// ==============================================
void MoveCursor(int Y, int X)
{
	//�o�͂�S�p�����œ��ꂵ�Ă���̂ŁAX��2�{�ɂ���
	std::cout << "\033[" << Y + 1 << ";" << 2 * X + 1 << "H";
}

// ==============================================
// �J�[�\�����\���ɂ���֐�
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
// �o�͂��镶���̐F��RGB�Ŏw�肷��֐�
// ==============================================
void ChangeCharColor(int r, int g, int b)
{
	std::cout << "\x1b[38;2;" << r << ";" << g << ";" << b << "m";
}

//�F���Z�b�g
void ChangeCharColor(void)
{
	std::cout << "\x1b[39m";
}

// ==============================================
// �o�͂���w�i�̐F��RGB�Ŏw�肷��֐�
// ==============================================
void ChangeBGColor(int r, int g, int b)
{
	std::cout << "\x1b[48;2;" << r << ";" << g << ";" << b << "m";
}

//�F���Z�b�g
void ChangeBGColor(void)
{
	std::cout << "\x1b[49m";
}