#include <fstream>
#include <sstream> 
#include <iostream>
#include <string>
#include "ItemManager.h"
#include "Type/GameTypes.h"
#include "Inventory/Item/ConsumableItem.h"

ItemManager::ItemManager()
{
	//LoadItemsFromFile("Data/ItemData.csv");
}

ItemManager::~ItemManager()
{
	for ( auto& pair : m_itemDataBase )
	{
		delete pair.second;
	}
	m_itemDataBase.clear();
}

const ItemBase* ItemManager::GetItem(const std::string & id)
{
	auto it = m_itemDataBase.find(id);
	if ( it != m_itemDataBase.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

void ItemManager::LoadItemsFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if ( !file.is_open() )
	{
		std::cerr << "해당 파일을 찾을 수 없음" << std::endl;
		return;
	}

	char utf8bom[3] = {};
	file.read(utf8bom , 3);

	if ( file.gcount() == 3 &&
		(unsigned char)utf8bom[0] == 0xEF &&
		(unsigned char)utf8bom[1] == 0xBB &&
		(unsigned char)utf8bom[2] == 0xBF )
	{
	}
	else
	{
		file.seekg(0);
	}

	std::string line;
	while ( std::getline(file , line) )
	{
		if ( !line.empty() && line.back() == '\r' )
		{
			line.pop_back();
		}

		if ( line.empty() || line[0] == '#' )
		{
			continue;
		}

		std::istringstream ss(line);
		std::string keyStr , name , rankStr , statStr , amountStr , isDamageStr;


		std::getline(ss , keyStr , ',');
		std::getline(ss , name , ',');
		std::getline(ss , rankStr , ',');
		std::getline(ss , statStr , ',');
		std::getline(ss , amountStr , ',');
		std::getline(ss , isDamageStr , ',');

		TargetStat targetState = StringToTargetStat(statStr);
		ItemRank itemRank = StringToItemRank(rankStr);
		int amount = std::stoi(amountStr);
		bool isDamage = (isDamageStr == "true" || isDamageStr == "1");

		// std::cout << "아이템 로드: " << keyStr << ", " << name << ", " << rankStr << ", " << statStr << ", " << amountStr << ", " << isDamageStr << std::endl;
		
		// 현재는 ConsumableItem만 할당하도록 구현되어 있으나, 다른 아이템 타입이 추가될 경우 데이터 시트에서 이를 구분한 후 예외처리를 할 수 있습니다.
		m_itemDataBase[keyStr] = new ConsumableItem(keyStr, name, itemRank, targetState, amount, isDamage);
	}
	file.close();
}

TargetStat ItemManager::StringToTargetStat(const std::string& str)
{
	if ( str == "HP" )
	{
		return TargetStat::HP;
	}
	else if ( str == "Stamina" )
	{
		return TargetStat::Stamina;
	}
	else if ( str == "Attack" )
	{
		return TargetStat::Attack;
	}
	else
	{
		std::cerr << "알 수 없는 TargetStat 문자열: " << str << std::endl;
		return TargetStat::HP; // 기본값으로 HP 반환
	}
}

ItemRank ItemManager::StringToItemRank(const std::string& str)
{
	if ( str == "Common" )
	{
		return ItemRank::Common;
	}
	else if ( str == "Rare" )
	{
		return ItemRank::Rare;
	}
	else if ( str == "Epic" )
	{
		return ItemRank::Epic;
	}
	else if ( str == "Legendary" )
	{
		return ItemRank::Legendary;
	}
	else
	{
		std::cerr << "알 수 없는 ItemRank 문자열: " << str << std::endl;
		return ItemRank::Common; // 기본값으로 Common 반환
	}
}
