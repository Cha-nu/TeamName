#include "GameManager.h"

#include <iostream>
#include <windows.h>

#include "../../Player/Player.h"
#include "../SceneManager/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene_M/StartScene/StartScene.h"

GameManager::GameManager() : IsRunning(true) , Character(nullptr)
{}

GameManager::~GameManager()
{
	Release();
}

bool GameManager::Init()
{
	SceneManager::getInstance().Add_Scene(new StartScene()); // 초기화면

	//마우스 클릭해도 화면이 안멈추게 하는 함수
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput , &prev_mode);
	// '빠른 편집 모드'를 꺼버리는 마법의 비트 연산
	SetConsoleMode(hInput , prev_mode & ~ENABLE_QUICK_EDIT_MODE);
	//////////////////////////////////////////////////////////////

	if ( DebugKey ) std::cout << "[GameManager] Init 완료" << '\n';
	return true;

}

void GameManager::Run()
{
	if (!Init()) return; // 초기화

	// 메인 게임 루프: 종료 조건이 만족될 때까지 반복
	while (IsRunning)
	{
		if ( DebugKey ) std::cout << "[GameManager] Update 진입" << '\n';
		Render();
		Update();

		// 임시 루프 종료 조건 (테스트용)
		// 실제로는 종료 화면이나 ESC 입력 시 IsRunning = false; 처리
	}

	Release();
}

void GameManager::Update()
{
	// 1. SceneManager를 통해 현재 씬의 로직 업데이트
	SceneManager::getInstance().Update();
	if ( DebugKey ) std::cout << "[GameManager] Update 완료" << '\n';
	// 2. 특정 조건(예: HP <= 0) 시 게임 오버 처리 등 공통 로직
}

void GameManager::Render()
{
	// 콘솔 화면 클리어 및 현재 씬 그리기
	system("cls");
	SceneManager::getInstance().Render();
	if ( DebugKey ) std::cout << "[GameManager] Render 완료" << '\n';
}

void GameManager::Exit()
{
	// ESC 누르면 호출
	// 현재 씬 일시정지
	//SceneManager::getInstance().Replace_Scene()
	if ( DebugKey ) std::cout << "[GameManager] Exit 완료" << '\n';
}

void GameManager::Release()
{
	SceneManager::getInstance().SceneStack_Clear();
    
	if ( DebugKey ) std::cout << "[GameManager] 시스템이 안전하게 종료되었습니다." << '\n';
}


void GameManager::SetPlayer(std::string& Name)
{
	if (Character)
	{
		delete Character; // 기존 플레이어 메모리 해제
	}
	Character = new Player(Name);
}

Player* GameManager::GetPlayer()
{
	return Character;
}