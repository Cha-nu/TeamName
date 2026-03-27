// 종료 화면.cpp

#include "EndScene.h"
#include "Manager/SceneManager/SceneManager.h" // Scene 매니저
#include "Scene_M/CreateScene/CreatingCharacter.h" // 씬 전환을 위해 추가

#include <iostream>
#include <string>
#include <cstdlib> // system의 cls, pause 사용하기 위해 추가

// 초기화 함수(1회 실행)
void GameOverScene::Init() {
	// 씬 진입 시 변수 초기화 및 추가할 변수 작성

	// 콘솔 화면을 깨끗히 지우기
	system("cls");
}

// 화면 출력
void GameOverScene::Render() {
	std::string Gameover = R"(

 _____                           _____                    
|  __ \                         |  _  |                   
| |  \/  __ _  _ __ ___    ___  | | | |__   __  ___  _ __ 
| | __  / _` || '_ ` _ \  / _ \ | | | |\ \ / / / _ \| '__|
| |_\ \| (_| || | | | | ||  __/ \ \_/ / \ V / |  __/| |   
 \____/ \__,_||_| |_| |_| \___|  \___/   \_/   \___||_|   
                                                          
                                                          
)";

	std::cout << Gameover << "\n";
	std::cout << "============================================================\n";
	std::cout << "                사회의 벽에 부딪혀 쓰러졌습니다..               \n";
	std::cout << "============================================================\n";

	std::cout << "============================================================\n";
	std::cout << "         1. 다시 시도                  2. 게임 나가기          \n";
	std::cout << "============================================================\n";
	std::cout << ">> 입력: ";
}

// 입력 및 로직 처리
void GameOverScene::Update() {
	int choice; // 사용자 입력
	std::cin >> choice;

	if (choice == 1) {
		std::cout << "============================================================\n";
		std::cout << "                    깨어나세요 용사여!!...                    \n";
		std::cout << "============================================================\n";
		system("pause"); // 잠시 멈추기(사용자에게 메시지 보여주기 위해 작성)

		// 생성 화면(CreateScene)으로 이동
		SceneManager::getInstance().Replace_Scene(new CharacterChoice());
	}
	else if (choice == 2) {
		std::cout << "============================================================\n";
		std::cout << "                      현실로 돌아갑니다...                    \n";
		std::cout << "============================================================\n";
		exit(0);
	}
	else {
		std::cout << "============================================================\n";
		std::cout << "               잘못된 입력입니다. 다시 입력하세요.              \n";
		std::cout << "============================================================\n";
		system("pause"); // 잠시 멈추기(사용자에게 메시지 보여주기 위해 작성)
	}
}

// 종료 함수
void GameOverScene::Exit() {
	// 씬을 나갈 때 메모리 해제 등의 필요한 부분이 있다면 작성
}