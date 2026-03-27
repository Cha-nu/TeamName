// 시작 화면.cpp

#include "StartScene.h"
#include "../../Manager/SceneManager/SceneManager.h" // Scene 매니저
#include "Scene_M/CreateScene/CreatingCharacter.h" // 씬 전환을 위해 추가

#include <iostream>
#include <string>
#include <windows.h> // [0327 추가] 좌표 이동(gotoxy), GetAsyncKeyState 사용을 위해 추가
// #include <cstdlib> // system의 cls, pause 사용하기 위해 추가

// [0327 추가] 지정한 X, Y 좌표로 콘솔 커서를 이동시키는 함수
void Start_gotoxy(int x , int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , pos);
}

// 초기화 함수(1회 실행)
void StartScene::Init() {
	// 씬 진입 시 변수 초기화 및 추가할 변수 작성
	currentIndex = 0; // [0327 추가] 게임 시작에 화살표가 있도록 초기화

	// 콘솔 화면을 깨끗히 지우기
	system("cls");
}

// 화면 출력
void StartScene::Render() {
	// 1. 타이틀 고정 출력 (콘솔 중앙쯤 위치하도록 좌표 설정)
	Start_gotoxy(30 , 5); std::cout << " _   __                                   ______ ______  _____ ";
	Start_gotoxy(30 , 6); std::cout << "| | / /                                   | ___ \\| ___ \\|  __ \\";
	Start_gotoxy(30 , 7); std::cout << "| |/ /   ______   _ __ ___    ___  _ __   | |_/ /| |_/ /| |  \\/";
	Start_gotoxy(30 , 8); std::cout << "|    \\  |______| | '_ ` _ \\  / _ \\| '_ \\  |    / |  __/ | | __ ";
	Start_gotoxy(30 , 9); std::cout << "| |\\  \\          | | | | | ||  __/| | | | | |\\ \\ | |    | |_\\ \\";
	Start_gotoxy(30 , 10); std::cout << "\\_| \\_/          |_| |_| |_| \\___||_| |_| \\_| \\_|\\_|    \\_____/";


	Start_gotoxy(40 , 12); std::cout << "=========================================";
	Start_gotoxy(40 , 13); std::cout << "             [ 한국 남자 RPG ]            ";
	Start_gotoxy(40 , 14); std::cout << "=========================================";

	// 2. 선택지 고정 출력
	Start_gotoxy(39 , 16); std::cout << "[이동: 방향키 | 상호작용: SPACE바, Enter키]";
	Start_gotoxy(53 , 18); std::cout << "* 게임 시작";
	Start_gotoxy(53 , 20); std::cout << "* 게임 나가기";

	// 3. 화살표 그리기 (기존 위치는 지우고 새 위치에 그리기)
	Start_gotoxy(48 , 18); std::cout << "   "; // 1번 앞 공백으로 지우기
	Start_gotoxy(48 , 20); std::cout << "   "; // 2번 앞 공백으로 지우기

	// 3-1. 화살표 그리기 (공백으로 지운 위치에 화살표 출력)
	if ( currentIndex == 0 ) {
		Start_gotoxy(48 , 18); std::cout << "->"; // 1번 위치에 화살표
	}
	else {
		Start_gotoxy(48 , 20); std::cout << "->"; // 2번 위치에 화살표
	}
}

// 입력 및 로직 처리
void StartScene::Update() {
	// 위쪽 방향키 누름
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		currentIndex = 0;
	}
	// 아래쪽 방향키 누름
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		currentIndex = 1;
	}

	// 스페이스바(VK_SPACE) 또는 엔터(VK_RETURN) 누름
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || GetAsyncKeyState(VK_RETURN) & 0x8000) {
		system("cls");

		if (currentIndex == 0) {
			Start_gotoxy(40 , 10); std::cout << "=========================================";
			Start_gotoxy(40 , 11); std::cout << "       한국 남자의 세계로 들어갑니다...      ";
			Start_gotoxy(40 , 12); std::cout << "=========================================";
			Sleep(1500); // 1.5초 대기 후 진행

			// 생성 화면(CreateScene)으로 이동
			SceneManager::getInstance().Replace_Scene(new CharacterChoice());
			return; // 씬이 교체되었으므로 Update 종료
		}
		else if (currentIndex == 1) {
			Start_gotoxy(40 , 10); std::cout << "=========================================";
			Start_gotoxy(40 , 11); std::cout << "            현실로 돌아갑니다...           ";
			Start_gotoxy(40 , 12); std::cout << "=========================================";
			Sleep(1000); // 1초 대기 후 진행
			exit(0);
		}
	}

	// 너무 빠른 중복 입력 방지 및 CPU 점유율 안정화를 위한 딜레이
	Sleep(30);
}

// 종료 함수
void StartScene::Exit() {
	// 씬을 나갈 때 메모리 해제 등의 필요한 부분이 있다면 작성
}