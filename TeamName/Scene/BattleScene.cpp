#include "MainScene.h"
#include"BattleScene.h"
#include"Player/Player.h"
#include"Monster/Monster.h"
#include"../Manager/GameManager/GameManager.h"
#include "../Manager/SceneManager/SceneManager.h"
#include<iostream>
#include<iomanip>
#include<Windows.h>

void BattleScene::Init()
{
	system("cls");
	player = GameManager::getInstance().GetPlayer();
	monster = new NormalMonster({ "Test Normal Mob", 100, 10, 10 });//몬스터 동적할당
	//몬스터 호출 수정
	
}

void BattleScene::Render()
{
	std::cout << R"(
         [ 플레이어 ]                      [ 적 ]
             
              O                              O
             /|\                            /|\
             / \                            / \
           HP: )"
		// ★ 왼쪽 정렬(left)로 무조건 4칸(setw)을 차지하게 만듭니다!
		<< std::left << std::setw(4) << player->Getstat().HP
		<< R"(                  HP: )"
		// 적 체력도 똑같이 4칸 고정!
		<< std::left << std::setw(4) << monster->getHealth()
		<< R"(
    ==================================================
    )";

	std::cout << R"(
  +------------------------------------------+
  | 몬스터가 튀어나왔다!                     |
  | 어떻게 할까?                             |
  +------------------------------------------+
  |  1. 공격한다            2. 가방(아이템)  |
  |  3. 도망친다           99. 게임 종료     |
  +------------------------------------------+
  ▶ 입력: )";
}

void BattleScene::Update()
{
	int input;
	std::cin >> input;

	if ( input == 1 )
	{
		//플레이어 공격
		std::cout << " 플레이어 공격" << std::endl;
		player->Attack(monster);

		//몬스터 공격
		std::cout << " 몬스터 공격" << std::endl;
		monster->attackPlayer(player);

		std::cout << "\n계속하려면 아무 키나 누르세요...\n";
		system("pause > nul"); // (> nul을 붙이면 지저분한 기본 시스템 메시지가 안 뜹니다)
	}
	else if ( input == 2 )
	{
		//여기 고민 부분 인벤토리 Scene을 만들지
		std::cout << "플레이어 아이템 목록: " << std::endl;
	}
	else if ( input == 3 )
	{
		SceneManager::getInstance().Return_Scene();
	}
	else if ( input == 99 )
	{
		GameManager::getInstance().SetRunning(false);
	}
	else
	{
		//잘못된 입력
	}
}

void BattleScene::Exit()
{
}

BattleScene::~BattleScene()
{
	//동적할당 받은 몬스터 메모리 해제
	delete monster;
}

