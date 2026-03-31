#include <random>
#include <iostream>
#include <iomanip>
#include "Shop.h"
#include "Player/Player.h"
#include "Inventory/Inventory.h"
#include "Inventory/Item/ItemBase.h"
#include "Manager/ItemManager/ItemManager.h"
#include"ConsoleHelper.h"

Shop::Shop()
{
	m_stockList.reserve(MAX_DISPLAY_NUM);
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

int Shop::DisplayStock(int shopState , int currentIndex , int startX , int startY) const
{
	Console_gotoxy(startX , startY++);
	std::cout << "======================== [ 상 점 ] ========================";

	if ( m_stockList.empty() )
	{
		std::cout << "현재 판매 중인 물건이 없습니다.";
		std::cout << "===========================================================";
		return startY;
	}
	Console_gotoxy(startX , startY++);
	std::cout << std::left
		<< std::setw(8) << "[번호]"
		<< std::setw(20) << "이름"
		<< std::setw(10) << "가격"
		<< "설명";
	Console_gotoxy(startX , startY++);
	std::cout << "-----------------------------------------------------------";

	for ( int i = 0; i < m_stockList.size(); i++ )
	{
		const ItemBase* item = m_stockList[i]; 

		if ( item != nullptr ) 
		{
			Console_gotoxy(startX , startY++); // 줄바꿈

			// shopState가 1(구매 리스트 진입)일 때만 화살표를 그림
			if ( shopState == 0 && currentIndex == i ) 
			{
				std::cout << "  ->  ";
			}
			else 
			{ 
				std::cout << "      ";
			}

			std::cout << "[" << std::right << std::setw(2) << (i + 1) << "]   ";

			// 이름, 가격(GetGold로 수정), 설명 출력 (끝에 \n 뺐음)
			std::cout << std::left << std::setw(17) << item->GetName()
				<< std::right << std::setw(4) << item->GetGold() << " G   "
				<< std::left << item->GetDescription();
		}
	}
	Console_gotoxy(startX , startY++);
	std::cout << "===========================================================";
	return startY;
}

int Shop::BuyItem(Player& player , int itemIndex)
{
	if (itemIndex < 0 || itemIndex >= m_stockList.size())
	{
		//std::cout << "잘못된 번호입니다. 다시 선택해주세요.\n";
		return -1; // 잘못된 접근
	}

	int playerGold = player.GetGoldAmount();
	if (playerGold - m_stockList[itemIndex]->GetGold() < 0)
	{
		//std::cout << "골드가 부족합니다.\n";
		return 1;// 1번: 골드 부족
	}
	else if (player.GetInventory()->IsFull())
	{
		//std::cout << "인벤토리가 가득 찼습니다. 아이템을 판매하여 공간을 확보하세요.\n";
		return 2; // 2번: 인벤토리 가득 참
	}
	else
	{
		//std::cout << "[" << m_stockList[itemIndex]->GetName() << "] 아이템을 구매하였습니다.\n";
		player.AcquireGold(-m_stockList[itemIndex]->GetGold());
		player.GetInventory()->AddItem(m_stockList[itemIndex]->GetID());
		m_stockList.erase(m_stockList.begin() + itemIndex);
		return 0; // 0번: 구매
	}
}

void Shop::SellItem(Player& player , int itemIndex)
{	
	const ItemBase* item = player.GetInventory()->GetItemSlot(itemIndex).GetItem();

	if (itemIndex < 0 || itemIndex >= player.GetInventory()->GetItemCount())
	{
		std::cout << "잘못된 번호입니다. 다시 선택해주세요.\n";
		return;
	}
	std::cout << "[" << item->GetName() << "] 아이템을 판매하였습니다.\n";

	// 판매 시에는 아이템 가격의 60%를 획득하나, 소수점은 버림 처리합니다.
	player.AcquireGold(static_cast<int>(item->GetGold() * 0.6f));
	player.GetInventory()->RemoveItem(item->GetID());
}
