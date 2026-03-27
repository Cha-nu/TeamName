#include "MainScene.h"
#include"BattleScene.h"
#include"Scene/InventoryScene.h"
#include "../Manager/SceneManager/SceneManager.h"
#include"Manager/GameManager/GameManager.h"
#include"Player/Player.h"
#include<iostream>
#include<Windows.h>

void Main_gotoxy(int x , int y) //나중에 함수빼서 한번에 관리하기
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , pos);
}

void MainScene::Init()
{
	system("cls");
	player = GameManager::getInstance().GetPlayer();
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
		SceneManager::getInstance().Add_Scene(new BattleScene());
	}
	else if ( input == 2 ) 
	{
		//받아온 플레이어의 get함수로 스탯 접근
		std::cout << " 플레이어 이름: " << player->Getstat().name << std::endl;
		std::cout << " 플레이어 HP: " << player->Getstat().HP << std::endl;
		std::cout << " 플레이어 공격력: " << player->Getstat().Atk_Damage << std::endl;
		std::cout << " 플레이어 레벨: " << player->Getstat().Level << std::endl;
		std::cout << " 플레이어 경험치: " << player->Getstat().EXP << std::endl;
		std::cout << "\n계속하려면 아무 키나 누르세요...\n";
		system("pause > nul"); // (> nul을 붙이면 지저분한 기본 시스템 메시지가 안 뜹니다)
	}
	else if ( input == 3 ) 
	{
		SceneManager::getInstance().Add_Scene(new InventoryScene());
	}
	else if ( input == 99 ) 
	{
		//게임 매니저 종료 함수 호출
		GameManager::getInstance().SetRunning(false);
	}
	else 
	{
		std::cout << "잘못된 입력입니다." << std::endl;
		//잘못된 입력
	}
}

void MainScene::Exit()
{
}
