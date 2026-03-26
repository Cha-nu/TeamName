// 게임 실행 파일입니다.

#include <iostream>
#include "Manager/GameManager/GameManager.h"
#include "Manager/SceneManager/SceneManager.h"
#include"TestScene\Test_Lobby.h"

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << "[INFO] 한글 출력 확인" << '\n';

    GameManager gameManager;

    // 게임 시작
    gameManager.Run();

	return 0;
}
