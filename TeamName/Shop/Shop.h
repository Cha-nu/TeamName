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

	void InitializeStock();
	void DisplayStock() const;
	void BuyItem(Player& player, int itemIndex);
	void SellItem(Player& player, int itemIndex);

	const std::vector<const ItemBase*>& GetStockList() { return m_stockList; }

private:
	std::vector<const ItemBase*> m_stockList;
};