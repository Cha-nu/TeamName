
// 게임 실행 파일입니다.

#include <iostream>
//#include "Manager/GameManager/GameManager.h"
#include "Manager/SceneManager/SceneManager.h"
#include"TestScene\Test_Lobby.h"

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	std::cout << "Hello World!\n";

	//게임 매니저 Init();
	//게임 매니저 Run();
	//게임 매니저 Release(); //여기에 만약 중간에 게임을 강제로 끄면 여기서 SceneManager에 남아있던 Scene들을 다 날려주기

	//씬 매니저 돌아가는지 테스트용
	SceneManager::getInstance().Add_Scene(new Test_Lobby());
	bool isRunning = true;
	while ( isRunning ) {
		SceneManager::getInstance().Render();
		SceneManager::getInstance().Update();
	}
	SceneManager::getInstance().SceneStack_Clear();
	//

	return 0;
}
