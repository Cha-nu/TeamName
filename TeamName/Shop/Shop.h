/*
* ItemManager로부터 정보를 받아와 상점에 진열할 아이템을 관리하는 클래스입니다.
* 현재는 아이템을 중복으로 받아올 수 있으며, 이는 의도에 따라 변경될 수 있습니다.
* 추후 ShopScene 클래스가 구현되면, 해당 클래스의 객체를 멤버 변수로 가지고 있어야 합니다.
* 
* 
*/

#pragma once
#include <vector>

#define MAX_DISPLAY_NUM 5

class ItemBase;
class Player;
class Shop
{
public:
	Shop();
	~Shop();

	// 상점의 재고를 초기화하는 함수입니다. 전투 종료 이후에 호출되어야 합니다.
	void InitializeStock();
	// 상점에 진열된 아이템을 출력하는 함수입니다.
	void DisplayStock() const;

	// 플레이어가 아이템을 구매하거나 판매하는 함수입니다. itemIndex는 상점에 진열된 아이템의 인덱스입니다.
	// 호출되기 전, DisplayStock() 함수를 통해 사용자에게 아이템의 인덱스를 보여주고 사용자의 입력을 받아야 합니다.
	void BuyItem(Player& player, int itemIndex);
	// 플레이어가 아이템을 판매하는 함수입니다. itemIndex는 플레이어의 인벤토리에 있는 아이템의 인덱스입니다.
	// 호출되기 전, 플레이어의 인벤토리를 보여주고(player.GetInventory()->PrintItemList()) 사용자의 입력을 받아야 합니다.
	void SellItem(Player& player, int itemIndex);

	const std::vector<const ItemBase*>& GetStockList() const { return m_stockList; }

private:
	// 상점에 진열된 아이템의 리스트입니다. 최대 MAX_DISPLAY_NUM개의 아이템이 진열될 수 있습니다.
	std::vector<const ItemBase*> m_stockList;
};