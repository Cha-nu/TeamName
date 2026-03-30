#include <random>
#include <iostream>
#include <iomanip>
#include "Shop.h"
#include "Player/Player.h"
#include "Inventory/Inventory.h"
#include "Inventory/Item/ItemBase.h"
#include "Manager/ItemManager/ItemManager.h"

Shop::Shop()
{

}

Shop::~Shop()
{

}

void Shop::InitializeStock()
{
	m_stockList.clear();
	ItemManager& itemManager = ItemManager::GetInstance();
	const std::vector<std::string>& itemIDs = itemManager.GetAllItemIDs();

	// 아래 3줄은 난수 생성을 위한 코드입니다.
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0 , static_cast<int>(itemIDs.size() - 1));

	for ( int i = 0; i < MAX_DISPLAY_NUM; i++ )
	{
		int randomIndex = dist(gen);
		std::string itemID = itemIDs[randomIndex];

		m_stockList.push_back(itemManager.GetItem(itemID));
	}
}

void Shop::DisplayStock() const
{
	std::cout << "\n======================== [ 상 점 ] ========================\n";

	if ( m_stockList.empty() )
	{
		std::cout << "현재 판매 중인 물건이 없습니다.\n";
		std::cout << "===========================================================\n";
		return;
	}

	std::cout << std::left
		<< std::setw(8) << "[번호]"
		<< std::setw(20) << "이름"
		<< std::setw(10) << "가격"
		<< "설명\n";
	std::cout << "-----------------------------------------------------------\n";

	for ( int i = 0; i < m_stockList.size(); i++ )
	{
		const ItemBase* item = m_stockList[i];

		if ( item != nullptr )
		{
			std::cout << "[" << std::right << std::setw(2) << (i + 1) << "]   ";

			std::cout << std::left << std::setw(17) << item->GetName()
				<< std::right << std::setw(4) << item->GetGold() << " G   "
				<< std::left << item->GetDescription() << "\n";
		}
	}
	std::cout << "===========================================================\n";
}
void Shop::BuyItem(Player& player , int itemIndex)
{
	
}

void Shop::SellItem(Player& player , int itemIndex)
{

}
