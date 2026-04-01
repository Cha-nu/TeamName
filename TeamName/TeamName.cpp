// 게임 실행 파일입니다.

#include <iostream>
#include <windows.h>
#include "Manager/GameManager/GameManager.h"

int main()
{
	// 전체화면 설정
	keybd_event(VK_F11 , 0 , 0 , 0);               // F11 누름
	keybd_event(VK_F11 , 0 , KEYEVENTF_KEYUP , 0);

	Sleep(1000);

	//커서 표시 여부
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle , &cursorInfo);
	cursorInfo.bVisible = FALSE; // 커서 표시 여부를 FALSE로 설정
	SetConsoleCursorInfo(consoleHandle , &cursorInfo);

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	/*std::cout << "[INFO] 한글 출력 확인" << '\n';*/

	// 게임 시작
	GameManager::getInstance().Run();
	
	// 콘솔 창 종료
	ExitProcess(0);
}
