// 게임 실행 파일입니다.

#include <iostream>
#include <windows.h>
#include "Manager/GameManager/GameManager.h"
#include "Manager/SceneManager/SceneManager.h"
#include "TestScene\Test_Lobby.h"

int main()
{
	// 전체화면 설정
	//keybd_event(VK_F11 , 0 , 0 , 0);               // F11 누름
	//keybd_event(VK_F11 , 0 , KEYEVENTF_KEYUP , 0);
	system("mode con cols=120 lines=30");

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	/*std::cout << "[INFO] 한글 출력 확인" << '\n';*/

	// 게임 시작
	GameManager::getInstance().Run();

	// 게임 종료
	GameManager::getInstance().Release();

	return 0;
}
