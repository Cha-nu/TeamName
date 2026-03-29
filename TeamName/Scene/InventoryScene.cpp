#include "InventoryScene.h"
#include"BattleScene.h"
#include "../Manager/SceneManager/SceneManager.h"
#include"Manager/GameManager/GameManager.h"
#include"Inventory/Inventory.h"
#include "Inventory/Item/ItemBase.h"
#include"Player/Player.h"
#include<iostream>
#include<iomanip>
#include"ConsoleHelper.h"

void InventoryScene::Init()
{
	system("cls");
	SetCursorVisible(false);//인벤토리 print 함수를 빌려와서 일단 가시성을 위해 사용하지만 나중에 한번 고민해봐야 할듯 
	player = GameManager::getInstance().GetPlayer();
	totalItems = player->GetInventory()->GetItemSlots().size();
	WaitUntilKeyUp_Enter_Space();
}

void InventoryScene::Render()
{
	player->GetInventory()->PrintItemList(inventoryState , currentIndex);//아이템 리스트 뽑는 구문

	if ( inventoryState == 0 && currentIndex == totalItems ) 
	{
		std::cout << "  ->  ";
	}
	else
	{
		std::cout << "      ";
	}

	std::cout << " 나가기 (이전 화면으로)\n";


	if ( inventoryState == 1 )
	{

		Console_gotoxy(popup_X , popup_Y);     std::cout << "+----------------------------------+";
		Console_gotoxy(popup_X , popup_Y + 1); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 2); std::cout << "|   이 아이템을 사용하시겠습니까?  |";
		Console_gotoxy(popup_X , popup_Y + 3); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 4); std::cout << "|             예                   |";
		Console_gotoxy(popup_X , popup_Y + 5); std::cout << "|             아니오               |";
		Console_gotoxy(popup_X , popup_Y + 6); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 7); std::cout << "+----------------------------------+";

		if ( confirmIndex == 0 ) 
		{ 
			Console_gotoxy(popup_X + 9 , popup_Y + 4); std::cout << "->"; // 예
		} 
		else if ( confirmIndex == 1 ) 
		{ 
			Console_gotoxy(popup_X + 9 , popup_Y + 5); std::cout << "->"; // 아니오
		} 
	}
}

void InventoryScene::Update()
{
	isKeyPressed = false;//키를 아직 안눌렀다고 인식
	if ( (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) )
	{
		isKeyPressed = true;//키를 눌렀다고 인식을 함
		WaitUntilKeyUp_Enter_Space();
	}

	if ( inventoryState == 0 ) 
	{
		if ( GetAsyncKeyState(VK_UP) & 0x8000 ) 
		{
			if ( currentIndex > 0 ) 
			{
				currentIndex--;//"->"위치를 올리는 부분 (콘솔 좌표는 왼쪽위가 0,0이다)
			}
		}
		else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) 
		{
			if ( currentIndex < totalItems ) 
			{
				currentIndex++;//"->"아래로 내리는  부분 
			} 
		}
		if ( isKeyPressed )
		{
			if ( currentIndex == totalItems )//제일 아이템 항목 아래인 나가기 버튼(전투씬으로 다시 가는) 위치
			{
				SceneManager::getInstance().Return_Scene();
			}
			else if ( totalItems > 0 )
			{
				inventoryState = 1;// 아이템을 선택한 경우 (팝업창 띄우기)
				confirmIndex = 0; // 팝업창 '예','아니오'선택지 위치 '예'부터 시작하게 고정
			}
		}
	}
	else if ( inventoryState == 1 ) 
	{
		if ( GetAsyncKeyState(VK_UP) & 0x8000 ) 
		{
			confirmIndex = 0; // 예 (위)
		}
		else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) 
		{
			confirmIndex = 1; // 아니오 (아래)
		}

		if ( isKeyPressed )
		{
			//if(confirmIndex == 0)//아이템 사용 로직!
			//플레이어가 Use를 쓴다
			//배틀씬으로 넘어갈 때 무슨 아이템을 썼는지 넘겨주기
			//SceneManager::getInstance().Return_Scene(); // 배틀 씬으로 복귀!
			//else if (confirmIndex == 1) //팝업창 닫고 리스트로 복귀

			if ( confirmIndex == 0 )//'예'를 누를시 아이템 사용 로직
			{
				SceneManager::getInstance().Set_UseItem_Name(player->GetInventory()->GetItemSlots()[currentIndex].GetItem()->GetName());
				//선택된 인덱스 번호의 아이템 이름을 게임 매니저한테 넘겨줘서 저장 시켜서 배틀씬에 사용함

				player->P_UseItem(currentIndex + 1);
				//currentIndex는 0번 부터 시작인데 P_UseItem에 로직에서 편리를 위해 1이 들어오면 매개변수값 -1로 접근해서 +1를 해주고 넘겨준다.

				SceneManager::getInstance().Return_Scene();//아이템을 사용했으니 내 턴을 사용한거라서 바로 배틀신으로 넘어오기
			}
			else if ( confirmIndex == 1 )//'아니요'를 누를시 팝업창이 닫히는 로직
			{
				inventoryState = 0;
			}
		}
	}
	Sleep(50);
}

void InventoryScene::Exit()
{
}
