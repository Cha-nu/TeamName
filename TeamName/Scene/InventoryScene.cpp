#include "InventoryScene.h"
#include"BattleScene.h"
#include "../Manager/SceneManager/SceneManager.h"
#include"Manager/GameManager/GameManager.h"
#include"Inventory\Inventory.h"
#include"Player/Player.h"
#include<iostream>
#include<iomanip>
#include<Windows.h>

void InventoryScene::Init()
{
	system("cls");
	player = GameManager::getInstance().GetPlayer();
	player_Inventory = player->GetInventory();
	player_ItemSlots = player_Inventory->GetItemSlots();
}

void InventoryScene::Render()
{
	std::cout << "========================================================" << std::endl;

	std::cout << "                   [ 내 가 방 ]                         " << std::endl;

	std::cout << "========================================================" << std::endl;
	// 배열이 비어있으면 텅 빈 가방이라고 출력합니다.
	if ( player_ItemSlots.empty() )
	{
		std::cout << "\n           가방이 텅 비어있습니다.           \n\n";
	}
	else
	{
		// player_Inventory->PrintItemList(); 아이템 리스트 띄우기
	}
	std::cout << "========================================================\n";
	std::cout << " 원하시는 아이템 번호를 입력하세요. (0번: 나가기)\n";
	std::cout << " ▶ 입력: ";
}

void InventoryScene::Update()
{
	int input;
	std::cin >> input;
	//int형말고 다른값 입력받았을 때 예외처리 해주기

	if ( input == 0 ) // 0번을 누르면 가방을 닫고 이전 씬(마을 또는 전투)으로 돌아갑니다!
	{
		SceneManager::getInstance().Return_Scene(); //
	}

	if ( input < 1 || input >(int)player_ItemSlots.size() || player_ItemSlots[input - 1].IsEmpty() ) 
		//음수를 입력했을 때 + ItemSlot범위 넘어서 접근할려고 할 때 + 사용해서 그 벡터가 비어있을때(erase쓰면 필요없긴 함)
	{
		std::cout << "[시스템] 잘못된 번호입니다. 다시 입력해주세요.\n";
		system("pause");
		return;
	}

	std::cout << "[시스템] " << player_ItemSlots[input - 1].GetItem()->GetName() << "을(를) 사용합니다." << std::endl;//input값이 1부터니까 인덱스에 접근할려면 -1을 해야 순서가 맞음
	// Use 부분 player가 그 아이템을 받고 써도되고 아이템이 플레이정보를 받고 수정해도되고


}

void InventoryScene::Exit()
{
}
