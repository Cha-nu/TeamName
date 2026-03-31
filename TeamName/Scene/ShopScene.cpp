#include <iostream>
#include <iomanip>
#include "ShopScene.h"
#include "Manager/SceneManager/SceneManager.h"
#include "Manager/GameManager/GameManager.h"
#include"Scene/InventoryScene.h"
#include "Player/Player.h"
#include "Inventory/Inventory.h"
#include "ConsoleHelper.h"
#include "BattleScene.h"

void ShopScene::Init()
{
	system("cls");
	SetCursorVisible(false);
	std::cin.clear();

	player = GameManager::getInstance().GetPlayer();
	m_shop.InitializeStock();


	// 중앙 배치 좌표 계산
	int cx , cy;
	GetScreen_Center_XY(cx , cy);
	shopX = cx - 35;
	shopY = cy - 10;

	// 스탯창을 오른쪽 공간에 배치
	statX = cx + 55;
	statY = cy - 10;

	//팝업창
	popup_X = cx - 17;
	popup_Y = cy - 2;
	

	shopState = 0;    // 처음 들어가면 상점 메인 메뉴
	currentIndex = 0;
	maxMenuIndex = m_shop.GetStockCount() + 1;

	SetNeedsRender(true);
	WaitUntilKeyUp_Enter_Space();
}

void ShopScene::Render()
{
	if ( !bNeedsRender )
	{
		return;
	}
	// 팝업창 지우는 함수 
	if ( shopState == 0 || shopState == 1 )
	{
		for ( int i = 0; i <= 7; i++ )
		{
			Console_gotoxy(popup_X , popup_Y + i);
			std::cout << "                                    "; // 36칸 공백
		}
	}

	//캐릭터 정보 
	Console_gotoxy(statX , statY);      std::cout << "+-----------------------+";
	Console_gotoxy(statX , statY + 1);  std::cout << "|   [ 캐릭터 정보 ]     |";
	Console_gotoxy(statX , statY + 2);  std::cout << "+-----------------------+";
	Console_gotoxy(statX , statY + 3);  std::cout << " 이름   : " << player->Getstat().name;
	Console_gotoxy(statX , statY + 4);  std::cout << " 레벨   : " << player->Getstat().Level;
	Console_gotoxy(statX , statY + 5);  std::cout << " HP     : " << player->Getstat().HP;
	Console_gotoxy(statX , statY + 6);  std::cout << " 공격력 : " << player->Getstat().Atk_Damage;
	Console_gotoxy(statX , statY + 7); std::cout << " Gold   : " << player->GetGoldAmount() << " G";
	Console_gotoxy(statX , statY + 8); std::cout << "+-----------------------+";

	nextY = m_shop.DisplayStock(shopState , currentIndex , shopX , shopY);

	stockCount = m_shop.GetStockCount();

	Console_gotoxy(shopX , nextY);

	if ( shopState == 0 && currentIndex == stockCount )//stock 다음 항목을 판단하는 UI
	{
		std::cout << "  ->  ";
	}
	else
	{
		std::cout << "      ";
	}
	std::cout << "[ 아이템 판매하기 (인벤토리 열기) ]            ";

	Console_gotoxy(shopX , nextY + 1);
	if ( shopState == 0 && currentIndex == stockCount + 1 ) 
	{
		std::cout << "  ->  ";
	}
	else 
	{
		std::cout << "      ";
	}
	std::cout << "[ 상점 나가기 (전투 시작) ]                   ";

	//구매 확인 팝업창 
	if ( shopState == 1 )
	{
		Console_gotoxy(popup_X , popup_Y);     std::cout << "+----------------------------------+";
		Console_gotoxy(popup_X , popup_Y + 1); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 2); std::cout << "|   이 아이템을 구매하시겠습니까?  |";
		Console_gotoxy(popup_X , popup_Y + 3); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 4); std::cout << "|             예                   |";
		Console_gotoxy(popup_X , popup_Y + 5); std::cout << "|             아니오               |";
		Console_gotoxy(popup_X , popup_Y + 6); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 7); std::cout << "+----------------------------------+";

		Console_gotoxy(popup_X + 9 , popup_Y + 4); std::cout << "  ";
		Console_gotoxy(popup_X + 9 , popup_Y + 5); std::cout << "  ";
		if ( confirmIndex == 0 ) 
		{ 
			Console_gotoxy(popup_X + 9 , popup_Y + 4); std::cout << "->"; 
		}
		else { 
			Console_gotoxy(popup_X + 9 , popup_Y + 5); std::cout << "->";
		}
	}
	else if ( shopState == 2 )//골드 부족 팝업
	{
		Console_gotoxy(popup_X , popup_Y);     std::cout << "+----------------------------------+";
		Console_gotoxy(popup_X , popup_Y + 1); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 2); std::cout << "|   골드가 부족하여 살 수 없습니다!|";
		Console_gotoxy(popup_X , popup_Y + 3); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 4); std::cout << "|           [ 확 인 ]              |";
		Console_gotoxy(popup_X , popup_Y + 5); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 6); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 7); std::cout << "+----------------------------------+";
		Console_gotoxy(popup_X + 9 , popup_Y + 4); std::cout << "->";
	}
	else if ( shopState == 3 ) //인벤토리 꽉 찼다는 팝업
	{
		Console_gotoxy(popup_X , popup_Y);     std::cout << "+----------------------------------+";
		Console_gotoxy(popup_X , popup_Y + 1); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 2); std::cout << "|  가방이 꽉 차서 살 수 없습니다!  |";
		Console_gotoxy(popup_X , popup_Y + 3); std::cout << "|  (아이템을 팔거나 사용하세요)    |";
		Console_gotoxy(popup_X , popup_Y + 4); std::cout << "|           [ 확 인 ]              |";
		Console_gotoxy(popup_X , popup_Y + 5); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 6); std::cout << "|                                  |";
		Console_gotoxy(popup_X , popup_Y + 7); std::cout << "+----------------------------------+";
		Console_gotoxy(popup_X + 9 , popup_Y + 4); std::cout << "->";
	}

	Console_gotoxy(0 , 0);
	SetNeedsRender(false);
}

void ShopScene::Update()
{
	isKeyPressed = false;
	if ( (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) )
	{
		isKeyPressed = true;
		WaitUntilKeyUp_Enter_Space();
		SetNeedsRender(true); // 렌더링
	}
	stockCount = m_shop.GetStockCount();
	if ( shopState == 0 ) // 목록 및 버튼 선택 모드
	{
		if ( GetAsyncKeyState(VK_UP) & 0x8000 ) 
		{ 
			if ( currentIndex > 0 ) 
			{ 
				currentIndex--; 
				SetNeedsRender(true); 
			}
			Sleep(100); //두개씩 넘어가는 현상 없앨려고 추가 
		}
		else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) 
		{ 
			if ( currentIndex < maxMenuIndex )
			{ 
				currentIndex++; 
				SetNeedsRender(true); 
			}
			Sleep(100);//두개씩 넘어가는 현상 없앨려고 추가
		}
		if ( isKeyPressed )
		{
			if ( currentIndex < stockCount ) // 상품 선택 시
			{
				shopState = 1; // 구매 확인 팝업
				confirmIndex = 0;
			}
			else if ( currentIndex == stockCount ) // 판매 버튼 선택 시
			{
				// 상점 모드로 인벤토리 열기
				//이때 상점에서 인벤토리를 들어간지 판단하기
				SceneManager::getInstance().Set_IsShopMode(true);
				SceneManager::getInstance().Add_Scene(new InventoryScene());//매개변수로 넘겨주면 어지러움
			}
			else if ( currentIndex == stockCount + 1 ) // 전투로 간다는 버튼을 누를시
			{
				//전투로 가는거
				SceneManager::getInstance().Replace_Scene(new BattleScene());
				return;//트러블 슈팅 해결
			}
			SetNeedsRender(true);
		}
	}
	else if ( shopState == 1 ) // 구매 확인 팝업 조작
	{
		if ( GetAsyncKeyState(VK_UP) & 0x8000 ) 
		{
			confirmIndex = 0;
			SetNeedsRender(true);
		}
		else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) 
		{
			confirmIndex = 1;
			SetNeedsRender(true);
		}
		if ( isKeyPressed ) 
		{
			if ( confirmIndex == 0 ) // '예' 선택
			{
				int buyResult = m_shop.BuyItem(*player , currentIndex);
				if ( buyResult == 0 ) // 성공 
				{
					system("cls");
					shopState = 0;
					maxMenuIndex = m_shop.GetStockCount() + 1; // 리스트 갱신
					//플레이어가 산 아이템을 상점 진열대(리스트)에서 아예 지워야 함
					//
				}
				else if ( buyResult == 1 ) //  골드 부족
				{
					shopState = 2; // 골드 부족 팝업
				}
				else if ( buyResult == 2 ) //  인벤토리 가득 참
				{
					shopState = 3; // 인벤토리 가득 참 팝업 
				}
			}
			else 
			{
				shopState = 0;
			}
			SetNeedsRender(true);
		}
	}
	else if ( shopState == 2 || shopState == 3 ) // 골드나 인벤토리 부족 팝업 조작
	{
		if ( isKeyPressed )
		{
			shopState = 0;
			SetNeedsRender(true);
		}
	}

	Sleep(50);
}

void ShopScene::Exit()
{
	system("cls");
}
