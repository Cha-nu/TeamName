#include "GameManager.h"
#include "../../Player/Player.h"
#include "../SceneManager/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene_M/StartScene/StartScene.h"

GameManager::GameManager(): IsRunning(true)
{

}

GameManager::~GameManager()
{
	Release();
}

bool GameManager::Init()
{
	SceneManager::getInstance().Add_Scene(new StartScene()); // 초기화면

	if ( DebugKey ) std::cout << "GameManager: Init 완료" << '\n';
	return true;

}

void GameManager::Run()
{
	if (!Init()) return; // 초기화

	// 메인 게임 루프: 종료 조건이 만족될 때까지 반복
	while (IsRunning)
	{
		if ( DebugKey ) std::cout << "GameManager: Update 진입" << '\n';
		Render();
		Update();

		// 임시 루프 종료 조건 (테스트용)
		// 실제로는 종료 화면이나 ESC 입력 시 IsRunning = false; 처리
		IsRunning = false;
	}

	Release();
}

void GameManager::Update()
{
	// 1. SceneManager를 통해 현재 씬의 로직 업데이트
	SceneManager::getInstance().Update();
	if ( DebugKey ) std::cout << "GameManager: Update 완료" << '\n';
	// 2. 특정 조건(예: HP <= 0) 시 게임 오버 처리 등 공통 로직
}

void GameManager::Render()
{
	// 콘솔 화면 클리어 및 현재 씬 그리기
	system("cls");
	SceneManager::getInstance().Render();
	if ( DebugKey ) std::cout << "GameManager: Render 완료" << '\n';
}

void GameManager::Exit()
{
}

void GameManager::Release()
{
	SceneManager::getInstance().SceneStack_Clear();
    
	std::cout << "[INFO] 시스템이 안전하게 종료되었습니다." << '\n';
}

void GameManager::CreatePlayer()
{
}
