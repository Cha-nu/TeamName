#include "GameManager.h"

#include <iostream>

#include "../../Player/Player.h"
#include "../SceneManager/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene_M/StartScene/StartScene.h"

// 몬스터 헤더 추가
#include "../../Monster/Monster.h"
#include "../../Monster/BossMonster.h"

GameManager::GameManager() : IsRunning(true) , Character(nullptr)
{}

GameManager::~GameManager()
{
	Release();
}

bool GameManager::Init()
{
	// 씬 매니저 초기화면
	SceneManager::getInstance().Add_Scene(new StartScene()); 

	// 스테이지별 몬스터 세팅
	// 0. 수능(튜토리얼보스) / 1. c언어(normal) / 2. c++(normal) / 3. graphics(normal) / 4. unreal(normal) / 5. 취업(최종보스)
	MonsterQueue.push(new BossMonster({ "수능", 10, 1, 200 }));       
	MonsterQueue.push(new NormalMonster({ "C언어", 10, 1, 200 }));      
	MonsterQueue.push(new NormalMonster({ "C++", 10, 1, 200 }));        
	MonsterQueue.push(new NormalMonster({ "Graphics", 10, 1, 200 }));   
	MonsterQueue.push(new NormalMonster({ "Unreal", 10, 1, 200 }));    
	MonsterQueue.push(new BossMonster({ "취업", 10, 1, 1000 }));    

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
	}

	Release();
}

void GameManager::Update()
{
	SceneManager::getInstance().Update();
	if ( DebugKey ) std::cout << "[GameManager] Update 완료" << '\n';
}

void GameManager::Render()
{
	system("cls");
	SceneManager::getInstance().Render();
	if ( DebugKey ) std::cout << "[GameManager] Render 완료" << '\n';
}

void GameManager::Exit()
{
	if ( DebugKey ) std::cout << "[GameManager] Exit 완료" << '\n';
}

void GameManager::Release()
{
	SceneManager::getInstance().SceneStack_Clear();

    // 큐 메모리 해제
	while (!MonsterQueue.empty())
	{
		delete MonsterQueue.front();
		MonsterQueue.pop();
	}
    
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

Monster* GameManager::ManageMonster()
{
	// 큐가 비어있지 않다면 가장 앞의 몬스터를 반환하고, 큐에서 pop
	if (!MonsterQueue.empty())
	{
		Monster* currentMonster = MonsterQueue.front();
		MonsterQueue.pop();
		return currentMonster;
	}

	// 몬스터가 더 이상 없으면 nullptr 반환 **예외처리 해주세요.**
	return nullptr;
}
