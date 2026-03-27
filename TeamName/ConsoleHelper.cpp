#include "ConsoleHelper.h"

void Console_gotoxy(int x , int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , pos);

}

void DisableQuickEdit()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput , &prev_mode);
	SetConsoleMode(hInput , prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void SetCursorVisible(bool isVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &cursorInfo);
	cursorInfo.bVisible = isVisible; // true면 보임, false면 숨김
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &cursorInfo);
}
