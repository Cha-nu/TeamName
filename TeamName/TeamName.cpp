// 게임 실행 파일입니다.

#include <iostream>
#include <windows.h>
#include "Manager/GameManager/GameManager.h"
<<<<<<< HEAD

#include "StartScene.h"
#include "CreatingCharacter.h"
#include "EndScene.h"
=======
#include "Manager/SceneManager/SceneManager.h"
#include "TestScene\Test_Lobby.h"
>>>>>>> update

int main()
{
	// 전체화면 설정
	//keybd_event(VK_F11 , 0 , 0 , 0);               // F11 누름
	//keybd_event(VK_F11 , 0 , KEYEVENTF_KEYUP , 0);
	system("mode con cols=120 lines=30"); // 화면 크기 설정

	//커서 표시 여부
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle , &cursorInfo);
	cursorInfo.bVisible = FALSE; // 커서 표시 여부를 FALSE로 설정
	SetConsoleCursorInfo(consoleHandle , &cursorInfo);

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	/*std::cout << "[INFO] 한글 출력 확인" << '\n';*/

<<<<<<< HEAD
	// 1. 시작 화면
	IntroScene startScene;
	startScene.Init();
	startScene.Render();
	startScene.Update();
	startScene.Exit();

	// 2. 캐릭터 생성 화면
	CharacterChoice createScene;
	createScene.Init();
	createScene.Render();
	createScene.Update();
	createScene.Exit();

	// 3. 종료 화면
	GameOverScene endScene;
	endScene.Init();
	endScene.Render();
	endScene.Update();
	endScene.Exit();
	
	// GameManager gameManager;

	// 게임 시작
	// gameManager.Run();

=======
	// 게임 시작
	GameManager::getInstance().Run();

	// 게임 종료
	GameManager::getInstance().Release();

>>>>>>> update
	return 0;
}
