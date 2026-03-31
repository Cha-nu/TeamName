// 시작 화면.cpp

#include "StartScene.h"
#include "Manager/SceneManager/SceneManager.h" // Scene 매니저
#include "Scene_M/CreateScene/CreatingCharacter.h" // 씬 전환을 위해 추가
#include "Manager/SoundManager/SoundManager.h"
#include <iostream>
#include <string>
#include <windows.h> // [0327 추가] 좌표 이동(gotoxy), GetAsyncKeyState 사용을 위해 추가

#include "Manager/GameManager/GameManager.h"
// #include <cstdlib> // system의 cls, pause 사용하기 위해 추가

// [0327 추가] 지정한 X, Y 좌표로 콘솔 커서를 이동시키는 함수
void Start_gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 화면의 중앙 좌표를 구하는 도우미 함수
static void GetScreenCenterXY(int& centerX, int& centerY) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	
	// 가로, 세로의 중앙 지점 계산
	centerX = width / 2;
	centerY = height / 2;
}

// 초기화 함수(1회 실행)
void StartScene::Init() {
	// 씬 진입 시 변수 초기화 및 추가할 변수 작성
	currentIndex = 0; // [0327 추가] 게임 시작에 화살표가 있도록 초기화
	SetNeedsRender(true); // 렌더링
	// 콘솔 화면을 깨끗히 지우기
	system("cls");
}

// 화면 출력
void StartScene::Render() {
	if (!bNeedsRender) return;

	int cx, cy;
	GetScreenCenterXY(cx, cy);

	// 1. 타이틀 고정 출력 (콘솔 중앙을 기준으로 상대 좌표 설정)
	Start_gotoxy(cx - 30, cy - 10); std::cout << " _   __                                   ______ ______  _____ ";
	Start_gotoxy(cx - 30, cy -  9); std::cout << "| | / /                                   | ___ \\| ___ \\|  __ \\";
	Start_gotoxy(cx - 30, cy -  8); std::cout << "| |/ /   ______   _ __ ___    ___  _ __   | |_/ /| |_/ /| |  \\/";
	Start_gotoxy(cx - 30, cy -  7); std::cout << "|    \\  |______| | '_ ` _ \\  / _ \\| '_ \\  |    / |  __/ | | __ ";
	Start_gotoxy(cx - 30, cy -  6); std::cout << "| |\\  \\          | | | | | ||  __/| | | | | |\\ \\ | |    | |_\\ \\";
	Start_gotoxy(cx - 30, cy -  5); std::cout << "\\_| \\_/          |_| |_| |_| \\___||_| |_| \\_| \\_|\\_|    \\_____/";


	Start_gotoxy(cx - 20, cy -  3); std::cout << "=========================================";
	Start_gotoxy(cx - 20, cy -  2); std::cout << "             [ 한국 남자 RPG ]            ";
	Start_gotoxy(cx - 20, cy -  1); std::cout << "=========================================";

	// 2. 선택지 고정 출력
	Start_gotoxy(cx - 16, cy + 1); std::cout << "[이동: 방향키 | 상호작용: Enter키]";
	Start_gotoxy(cx - 7, cy + 3);  std::cout << "* 게임 시작";
	Start_gotoxy(cx - 7, cy + 5);  std::cout << "* 게임 나가기";

	// 3. 화살표 그리기 (기존 위치는 지우고 새 위치에 그리기)
	Start_gotoxy(cx - 10, cy + 3); std::cout << "  "; // 1번 앞 공백으로 지우기 (특수문자 크기 고려 2칸)
	Start_gotoxy(cx - 10, cy + 5); std::cout << "  "; // 2번 앞 공백으로 지우기

	// 3-1. 화살표 그리기 (공백으로 지운 위치에 화살표 출력)
	if (currentIndex == 0) {
		Start_gotoxy(cx - 10, cy + 3); std::cout << "▶"; // 1번 위치에 화살표
	}
	else {
		Start_gotoxy(cx - 10, cy + 5); std::cout << "▶"; // 2번 위치에 화살표
	}
	SetNeedsRender(false); // 렌더링 잠금
}

// 입력 및 로직 처리
void StartScene::Update() {
	// 위쪽 방향키 누름
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if ( currentIndex != 0 ) 
		{
			SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
		}
		currentIndex = 0;
		SetNeedsRender(true); // 렌더링
	}
	// 아래쪽 방향키 누름
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) 
	{
		if ( currentIndex != 1 ) 
		{
			SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
		}
		currentIndex = 1;
		SetNeedsRender(true); // 렌더링
	}

	// 엔터(VK_RETURN) 누름
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) 
	{
		SetNeedsRender(true); // 렌더링
		system("cls");

		int cx, cy;
		GetScreenCenterXY(cx, cy);

		if (currentIndex == 0) {
			Start_gotoxy(cx - 20, cy - 5); std::cout << "=========================================";
			Start_gotoxy(cx - 20, cy - 4); std::cout << "       한국 남자의 세계로 들어갑니다...      ";
			Start_gotoxy(cx - 20, cy - 3); std::cout << "=========================================";
			Sleep(1000); // 1초 대기 후 진행

			// 생성 화면(CreateScene)으로 이동
			SceneManager::getInstance().Replace_Scene(new CharacterChoice());
			return; // 씬이 교체되었으므로 Update 종료
		}
		else if (currentIndex == 1) {
			Start_gotoxy(cx - 20, cy - 5); std::cout << "=========================================";
			Start_gotoxy(cx - 20, cy - 4); std::cout << "            현실로 돌아갑니다...           ";
			Start_gotoxy(cx - 20, cy - 3); std::cout << "=========================================";
			Sleep(500); // 0.5초 대기 후 진행
			// 메모리 해제 후 게임 종료
			GameManager::getInstance().SetRunning(false);

			return;
		}
	}

	// 너무 빠른 중복 입력 방지 및 CPU 점유율 안정화를 위한 딜레이
	Sleep(20);
}

// 종료 함수
void StartScene::Exit() {
	// 씬을 나갈 때 메모리 해제 등의 필요한 부분이 있다면 작성
}