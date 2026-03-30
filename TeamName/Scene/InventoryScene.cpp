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
	std::cin.clear();// 입력 버퍼 초기화
	SetNeedsRender(true); // 렌더링
	player = GameManager::getInstance().GetPlayer();
	totalItems = player->GetInventory()->GetItemSlots().size();


	int cx , cy;
	GetScreen_Center_XY(cx , cy); // 헬퍼 함수 호출

	invX = cx - 31; // 인벤토리 폭(62)의 절반을 왼쪽으로
	invY = cy - 10; // 중앙보다 살짝 위에서 시작

	popup_X = cx - 17; // 팝업창 폭의 절반
	popup_Y = cy - 2;  // 화면 정중앙 부근


	WaitUntilKeyUp_Enter_Space();
}

void InventoryScene::Render()
{
	if ( !bNeedsRender ) 
	{ 
		return;
	}

	if ( inventoryState == 0 )
	{
		for ( int i = 0; i <= 7; i++ )
		{
			// 헤더에 저장된 popup_X, popup_Y 사용!
			Console_gotoxy(popup_X , popup_Y + i);
			std::cout << "                                    "; // 36칸 공백 지우개
		}
	}

	nextY = player->GetInventory()->PrintItemList(inventoryState , currentIndex , invX , invY);
	Console_gotoxy(invX , nextY);
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

		// 팝업창 내부 화살표 지우개
		//Console_gotoxy(popup_X + 9 , popup_Y + 4); std::cout << "  ";
		//Console_gotoxy(popup_X + 9 , popup_Y + 5); std::cout << "  ";
		if ( confirmIndex == 0 ) 
		{ 
			Console_gotoxy(popup_X + 9 , popup_Y + 4); std::cout << "->"; // 예
		} 
		else if ( confirmIndex == 1 ) 
		{ 
			Console_gotoxy(popup_X + 9 , popup_Y + 5); std::cout << "->"; // 아니오
		} 
	}
	else if ( inventoryState == 2 ) //전투 상태가 아닐 때 아이템을 사용할시 나오는 텍스트 창
	{
		// 사용 불가 경고 팝업창
		Console_gotoxy(popup_X , popup_Y);     std::cout << "+----------------------------------+";
		Console_gotoxy(popup_X , popup_Y + 1); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 2); std::cout << "| 전투 중에만 사용할 수 있습니다!  |";
		Console_gotoxy(popup_X , popup_Y + 3); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 4); std::cout << "|           [ 확 인 ]              |";
		Console_gotoxy(popup_X , popup_Y + 5); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 6); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 7); std::cout << "+----------------------------------+";

		Console_gotoxy(popup_X + 9 , popup_Y + 4); std::cout << "->"; // 확인 버튼 고정
	}
	Console_gotoxy(0 , 0);
	SetNeedsRender(false);
}

void InventoryScene::Update()
{
	isKeyPressed = false;//키를 아직 안눌렀다고 인식
	if ( (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) )
	{
		isKeyPressed = true;//키를 눌렀다고 인식을 함
		WaitUntilKeyUp_Enter_Space();
		SetNeedsRender(true);
	}

	if ( inventoryState == 0 ) 
	{
		if ( GetAsyncKeyState(VK_UP) & 0x8000 ) 
		{
			if ( currentIndex > 0 ) 
			{
				currentIndex--;//"->"위치를 올리는 부분 (콘솔 좌표는 왼쪽위가 0,0이다)
			}
			SetNeedsRender(true);
		}
		else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) 
		{
			if ( currentIndex < totalItems ) 
			{
				currentIndex++;//"->"아래로 내리는  부분 
			} 
			SetNeedsRender(true);
		}
		if ( isKeyPressed )
		{
			if ( currentIndex == totalItems )//제일 아이템 항목 아래인 나가기 버튼(전투씬으로 다시 가는) 위치
			{
				SceneManager::getInstance().Return_Scene();
			}
			else if ( totalItems > 0 )
			{
				if ( player->bIsPlayerBattle() == true ) //전투 상태일 때 나오는 창
				{
					inventoryState = 1;// 아이템을 선택한 경우 (팝업창 띄우기)
					confirmIndex = 0; // 팝업창 '예','아니오'선택지 위치 '예'부터 시작하게 고정
				}
				else 
				{
					inventoryState = 2;
				}
			}
			SetNeedsRender(true);
		}
	}
	else if ( inventoryState == 1 ) 
	{
		if ( GetAsyncKeyState(VK_UP) & 0x8000 ) 
		{
			confirmIndex = 0; // 예 (위)
			SetNeedsRender(true);
		}
		else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) 
		{
			confirmIndex = 1; // 아니오 (아래)
			SetNeedsRender(true);
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
			SetNeedsRender(true);
		}
	}
	else if ( inventoryState == 2 ) 
	{
		if ( isKeyPressed )
		{
			inventoryState = 0;
			SetNeedsRender(true);
		}
	}
	
	Sleep(50);
}

void InventoryScene::Exit()
{
	system("cls");
}
