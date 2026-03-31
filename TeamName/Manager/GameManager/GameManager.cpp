#include "GameManager.h"

#include <iostream>
#include"ConsoleHelper.h"//여기에 windows.h 이미 선언되어있습니다.

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

	void DisableQuickEdit();//마우스 클릭해도 화면이 안멈추게 하는 함수

	//if ( DebugKey ) std::cout << "[GameManager] Init 완료" << '\n';
	return true;

}

void GameManager::Run()
{
	if (!Init()) return; // 초기화

	// 메인 게임 루프: 종료 조건이 만족될 때까지 반복
	while (IsRunning)
	{
		//if ( DebugKey ) std::cout << "[GameManager] Update 진입" << '\n';
		Render();
		Update();
	}

	Release();
}

void GameManager::Update()
{
	SceneManager::getInstance().Update();
	//if ( DebugKey ) std::cout << "[GameManager] Update 완료" << '\n';
}

void GameManager::Render()
{
	SceneManager::getInstance().Render();
	//if ( DebugKey ) std::cout << "[GameManager] Render 완료" << '\n';
}

void GameManager::Exit()
{
	//if ( DebugKey ) std::cout << "[GameManager] Exit 완료" << '\n';
}

void GameManager::Release()
{
	SceneManager::getInstance().SceneStack_Clear();

	// 플레이어 메모리 해제
	if (Character)
	{
		delete Character;
		Character = nullptr;
	}
	if (CurrentMonster)
	{
		delete CurrentMonster;
		CurrentMonster = nullptr;
	}

    
	//if ( DebugKey ) std::cout << "[GameManager] 시스템이 안전하게 종료되었습니다." << '\n';
}

void GameManager::SetPlayer(std::string& Name)
{
	Character = new Player(Name);
}

Player* GameManager::GetPlayer()
{
	return Character;
}

Monster* GameManager::GetMonster() const
{
	return CurrentMonster;
}

bool GameManager::CreateMonster()
{
	int level = Character->Getstat().Level;
	if ( level < 2)
	{
		CurrentMonster = new BossMonster({ "수능", 10, 1, 120 });
		return true;
	}
	else if (level < 10)
	{
		delete CurrentMonster;
		int randomMonsterNum = rand() % static_cast<int>(MonsterName.size()); // 몬스터 수에 맞춰 랜덤 번호 생성
		//std::cout << "랜덤 몬스터 번호: " << randomMonsterNum << '\n'; // 디버그용 랜덤 번호 출력	
		if (DebugKey) CurrentMonster = new NormalMonster({ MonsterName[randomMonsterNum], 1, 1, 100 });
		else CurrentMonster = new NormalMonster({ MonsterName[randomMonsterNum], level*20, level*5, level * 10 });
	}
	else if ( level >= 10 )
	{
		delete CurrentMonster;
		if (DebugKey) CurrentMonster = new BossMonster({ "취업", 1, 1, 0 });
		else CurrentMonster = new BossMonster({ "취업",level * 300 , level * 10, 0 });
	}
	return false;
}

