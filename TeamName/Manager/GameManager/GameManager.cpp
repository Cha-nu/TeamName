#include "GameManager.h"

#include <iostream>
#include"ConsoleHelper.h"

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
	system("cls");
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

	
	std::cout << "[GameManager] 게임이 안전하게 종료되었습니다." << '\n';
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
		if ( DebugKey ) CurrentMonster = new BossMonster({ "수능", 1, 1, 500 });
		else CurrentMonster = new BossMonster({ "수능", 60, 1, 100 });
		return true;
	}
	else if (level < 10)
	{
		delete CurrentMonster;
		int randomMonsterNum = rand() % static_cast<int>(MonsterName.size()); // 몬스터 수에 맞춰 랜덤 번호 생성

		// 레벨 2~3 (ATK 40~55) -> 몬스터 HP 170~205 (약 3~4방)
		// 레벨 8~9 (ATK 205~250) -> 몬스터 HP 380~415 (약 1.5~2방)
		int monsterHP = 100 + (level * 35) + (rand() % 30); // 100 + (레벨*35) 단위의 체력에 약간의 랜덤 체력 변수(0~29) 부여
		int monsterAtk = 5 + (level * 8);                         // 적당한 공격력 증가량 (레벨 2~3: 16~24, 레벨 8~9: 64~72)
		int monsterExp = 20 + (level * 10);                 // 안정적인 레벨업을 위한 경험치량

		if (DebugKey) CurrentMonster = new NormalMonster({ MonsterName[randomMonsterNum], 1, 1, 500 });
		else CurrentMonster = new NormalMonster({ MonsterName[randomMonsterNum], monsterHP, monsterAtk, monsterExp });
	}
	else if ( level >= 10 )
	{
		delete CurrentMonster;

		// 플레이어 Lv.10 체력은 약 1280
		// 보스 공격력을 650으로 설정 (퀴즈 2번 틀리면 패배)
		// 보스 체력을 2400으로 설정하면 유저가 8번 공격해야(ATK 300 기준) 클리어.
		int bossHP = 2400;
		int bossAtk = 650;

		if (DebugKey) CurrentMonster = new BossMonster({ "취업", 1, 1, 0 });
		else CurrentMonster = new BossMonster({ "취업", bossHP, bossAtk, 0 });
	}
	return false;
}

