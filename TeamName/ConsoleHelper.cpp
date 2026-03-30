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

void WaitUntilKeyUp_Enter_Space() //Enter 또는 Space키 가 떼어질 때까지 프로그램의 실행을 일시 정지시키는 기능
{
	while ( (GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_SPACE) & 0x8000) ) 
	{
		Sleep(10);
	}
}

void GetScreen_Center_XY(int& centerX , int& centerY) 
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	// 가로, 세로의 중앙 지점 계산
	centerX = width / 2;
	centerY = height / 2;
}