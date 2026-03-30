#include <iostream>
#include <iomanip>
#include "ShopScene.h"
#include "Manager/SceneManager/SceneManager.h"
#include "Manager/GameManager/GameManager.h"
#include "Player/Player.h"
#include "Inventory/Inventory.h"
#include "ConsoleHelper.h"

void ShopScene::Init()
{
	system("cls");
	SetCursorVisible(false);
	std::cin.clear();

	player = GameManager::getInstance().GetPlayer();
	m_shop.InitializeStock();

	shopState = 0;    // 처음 들어가면 상점 메인 메뉴
	currentIndex = 0;
	totalListCount = 2; // 0: 구매, 1: 판매, 2: 나가기 (총 3개 항목이므로 인덱스 최대값은 2)

	SetNeedsRender(true);
	WaitUntilKeyUp_Enter_Space();
}

void ShopScene::Render()
{
	if ( !bNeedsRender )
	{
		return;
	}

	isKeyPressed = false;//키를 아직 안눌렀다고 인식
	if ( (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) )
	{
		isKeyPressed = true;//키를 눌렀다고 인식을 함
		WaitUntilKeyUp_Enter_Space();
		SetNeedsRender(true);
	}

	if ( shopState == 0 ) // 상점 메인 메뉴
	{
		// currentIndex(0, 1, 2)에 따라 아이템 구매, 판매, 나가기 메뉴를 표시
	}
	else if ( shopState == 1 ) // 구매 메뉴
	{
		m_shop.DisplayStock(); // 상점의 재고 아이템을 표시, 구매 메뉴 화면에 들어설 때마다 재고가 표시되어야 합니다.

		/* 렌더링 로직 추가 */
	}
	else if ( shopState == 2 ) // 판매 메뉴
	{
		player->GetInventory()->PrintItemList() ; // 플레이어의 인벤토리 아이템을 표시, 판매 메뉴 화면에 들어설 때마다 인벤토리가 표시되어야 합니다.

		/* 렌더링 로직 추가 */
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

	if ( shopState == 0 )
	{
		// currentIndex(0, 1, 2)에 따라 아이템 구매, 판매, 나가기 로직 처리
	}
	// 구매/판매 함수 내부에서는 모두 대상만 다를 뿐, 유사한 로직을 처리합니다.(선택한 아이템의 골드 가격 확인 후 구매/판매, 선택 시 즉시 구매/판매 처리, 골드 증감 로직)
	else if ( shopState == 1 )
	{
		// 여기서는 구매 메뉴에서의 로직을 처리해야 합니다.
		// m_shop.BuyItem(*player, currentIndex)를 넘겨줘야 합니다.
		// shop은 std::vector<const ItemBase*> m_stockList로 진열 아이템을 지니고 있으므로, 첫 인덱스는 0부터 시작합니다.
	}
	else if ( shopState == 2 )
	{
		// 여기서는 판매 메뉴에서의 로직을 처리해야 합니다.
		// m_shop.SellItem(*player, currentIndex)를 넘겨줘야 합니다.
		// Player Inventory 또한 std::vector<ItemSlot> m_itemSlots로 아이템을 지니므로, 첫 인덱스는 0부터 시작합니다.
	}

	Sleep(50);
}

void ShopScene::Exit()
{
	system("cls");
}
