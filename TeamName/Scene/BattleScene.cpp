#include "MainScene.h"
#include"BattleScene.h"
#include "../Manager/SceneManager/SceneManager.h"
#include<iostream>
#include<Windows.h>
void BattleScene::Init()
{
	system("cls");
	//player = 게임 매니저에서 받아온다
	//몬스터 여기서 동적 할당으로 생성
}

void BattleScene::Render()
{
	std::cout << R"(
         [ 플레이어 ]                      [ 적 ]
             
              O                              O
             /|\                            /|\
             / \                            / \
             
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
		//몬스터 공격
		std::cout << " 몬스터 공격" << std::endl;
	}
	else if ( input == 2 )
	{
		//여기 고민 부분 인벤토리 Scene을 만들지
		std::cout << "플레이어 아이템 목록: " << std::endl;
	}
	else if ( input == 3 )
	{
		SceneManager::getInstance().Replace_Scene(new MainScene());
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

void BattleScene::Exit()
{
}
