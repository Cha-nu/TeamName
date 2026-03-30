// 엔딩 화면.cpp

#include "EndingScene.h"
#include "Manager/SceneManager/SceneManager.h" // Scene 매니저
#include "Scene_M/StartScene/StartScene.h" // 씬 전환을 위해 추가

#include <iostream>
#include <string>
#include <windows.h> // 좌표 이동(gotoxy), GetAsyncKeyState 사용을 위해 추가

// 지정한 X , Y 좌표로 콘솔 커서를 이동시키는 함수
void Ending_gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , pos);
}

// 초기화 함수 (1회 실행)
void EndingScene::Init() {
	// 씬 진입 시 변수 초기화 및 추가할 변수 작성
	currentIndex = 0;
	SetNeedsRender(true); // 렌더링
	// 콘솔 화면 깨끗히 지우기
	system("cls");
}

// 화면 출력
void EndingScene::Render() {
	if ( !bNeedsRender ) return;
	// 타이틀 고정 출력 (콘솔 중앙쯤 위치하도록 좌표 설정)
	Ending_gotoxy(40 , 5); std::cout << " _   _  _        _                        _ ";
	Ending_gotoxy(40 , 6); std::cout << "| | | |(_)      | |                      | |";
	Ending_gotoxy(40 , 7); std::cout << "| | | | _   ___ | |_   ___   _ __  _   _ | |";
	Ending_gotoxy(40 , 8); std::cout << "| | | || | / __|| __| / _ \\ | '__|| | | || |";
	Ending_gotoxy(40 , 9); std::cout << "\\ \\_/ /| || (__ | |_ | (_) || |   | |_| ||_|";
	Ending_gotoxy(40 , 10); std::cout << " \\___/ |_| \\___| \\__| \\___/ |_|    \\__, |(_)";
	Ending_gotoxy(40 , 11); std::cout << "                                    __/ |   ";
	Ending_gotoxy(40 , 12); std::cout << "                                   |___/    ";

	Ending_gotoxy(40 , 14); std::cout << "=========================================";
	Ending_gotoxy(40 , 15); std::cout << "            취업에 성공했습니다!            ";
	Ending_gotoxy(40 , 16); std::cout << "=========================================";

	Ending_gotoxy(53 , 18); std::cout << "* 다시 시작";
	Ending_gotoxy(53 , 20); std::cout << "* 게임 나가기";

	// 3. 화살표 그리기 (기존 위치는 지우고 새 위치에 그리기)
	Ending_gotoxy(50 , 18); std::cout << " "; // 1번 앞 공백으로 지우기
	Ending_gotoxy(50 , 20); std::cout << " "; // 2번 앞 공백으로 지우기

	// 3-1. 화살표 그리기 (공백으로 지운 위치에 화살표 출력)
	if ( currentIndex == 0 ) {
		Ending_gotoxy(50 , 18); std::cout << "▶"; // 1번 위치에 화살표
	}
	else {
		Ending_gotoxy(50 , 20); std::cout << "▶"; // 2번 위치에 화살표
	}
	SetNeedsRender(false); // 렌더링 잠금
}

// 입력 및 로직 처리
void EndingScene::Update() {
	// 위쪽 방향키 누름
	if ( GetAsyncKeyState(VK_UP) & 0x8000 ) {
		currentIndex = 0;
		SetNeedsRender(true); // 렌더링
	}
	// 아래쪽 방향키 누름
	if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) {
		currentIndex = 1;
		SetNeedsRender(true); // 렌더링
	}

	// 엔터(VK_RETURN) 누름
	if ( GetAsyncKeyState(VK_RETURN) & 0x8000 ) {
		SetNeedsRender(true); // 렌더링
		system("cls");

		if ( currentIndex == 0 ) {
			Ending_gotoxy(40 , 10); std::cout << "=========================================";
			Ending_gotoxy(40 , 11); std::cout << "               돌아가는 중...             ";
			Ending_gotoxy(40 , 12); std::cout << "=========================================";
			Sleep(1500); // 1.5초 대기 후 진행

			// 생성 화면(CreateScene)으로 이동
			SceneManager::getInstance().Replace_Scene(new StartScene());
			return; // 씬이 교체되었으므로 Update 종료
		}
		else if ( currentIndex == 1 ) {
			Ending_gotoxy(40 , 10); std::cout << "=========================================";
			Ending_gotoxy(40 , 11); std::cout << "            현실로 돌아갑니다...           ";
			Ending_gotoxy(40 , 12); std::cout << "=========================================";
			Sleep(1000); // 1초 대기 후 진행
			exit(0);
		}
	}

	// 너무 빠른 중복 입력 방지 및 CPU 점유율 안정화를 위한 딜레이
	Sleep(20);
}

// 종료 함수
void EndingScene::Exit() {
	// 씬 나갈 때 메모리 해제 등이 필요하면 작성
}