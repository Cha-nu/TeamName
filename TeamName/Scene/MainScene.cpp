#include "MainScene.h"
#include"BattleScene.h"
#include "../Manager/SceneManager/SceneManager.h"
#include<iostream>
#include<Windows.h>
void MainScene::Init()
{
	system("cls");
	// player = 게임 매니저한테 받기
}

void MainScene::Render()
{
	std::cout << R"(
         .---------------------------.
         |  _______________________  |
         | |                       | |
         | |  C:\> _               | |
         | |                       | |
         | |_______________________| |
         |                           |
         `---------------------------`
               |  |         |  |
        _______|__|_________|__|_______
       /       [==========]            \
      /  [ ][ ][ ][ ][ ][ ][ ][ ][ ]    \
     /                                   \
    '====================================='
    )" << "\n";

	std::cout << R"(
  +------------------------------------------+
  | [ 방 ]                                   |
  | 다음 목적지를 선택해 주세요.             |
  +------------------------------------------+
  |  1. 전투      2. 캐릭터 능력치 확인      |
  |  3. 아이템 확인      99. 게임 종료       |
  +------------------------------------------+
  ▶ 입력: )";
}

void MainScene::Update()
{
	int input;
	std::cin >> input;

	if ( input == 1 ) 
	{
		SceneManager::getInstance().Replace_Scene(new BattleScene());
	}
	else if ( input == 2 ) 
	{
		//받아온 플레이어의 get함수로 스탯 접근
		std::cout << " 플레이어 HP: " << std::endl;
		std::cout << " 플레이어 공격력: " << std::endl;
		std::cout << " 플레이어 경험치: " << std::endl;
	}
	else if ( input == 3 ) 
	{
		//여기 고민 부분 인벤토리 Scene을 만들지
		std::cout << "플레이어 아이템 목록: " << std::endl;
	}
	else if ( input == 99 ) 
	{
		//게임 매니저 종료 함수 호출
	}
	else 
	{
		//잘못된 입력
	}
}

void MainScene::Exit()
{
}
