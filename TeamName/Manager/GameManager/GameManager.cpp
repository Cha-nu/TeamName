
#include "GameManager.h"

#include <conio.h> // _getch() 등을 이용한 입력 처리용

#include "Player.h"
#include "SceneManager.h"

GameManager::GameManager(): IsRunning(true)
{

}

GameManager::~GameManager()
{
    Release();
}

bool GameManager::Init()
{
    std::cout << "[INFO] 게임 시스템 초기화 중..." << '\n';

    return true;
}

void GameManager::Run()
{
    if (!Init()) return; // 초기화

    // 메인 게임 루프: 종료 조건이 만족될 때까지 반복
    while (IsRunning)
	{
        Update();
        Render();

        // 임시 루프 종료 조건 (테스트용)
        // 실제로는 종료 화면이나 ESC 입력 시 m_bIsRunning = false; 처리
    }

    Release();
}

void GameManager::Update()
{
    // 1. SceneManager를 통해 현재 씬의 로직 업데이트
    // m_pSceneManager->Update();

    // 2. 특정 조건(예: HP <= 0) 시 게임 오버 처리 등 공통 로직
}

void GameManager::Render()
{
    // 콘솔 화면 클리어 및 현재 씬 그리기
    // system("cls");
    // m_pSceneManager->Render();
}

void GameManager::Exit()
{
}

void GameManager::Release()
{
    
    std::cout << "[INFO] 시스템이 안전하게 종료되었습니다." << '\n';
}

void GameManager::CreatePlayer()
{
}
