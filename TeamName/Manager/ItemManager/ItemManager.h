/*
* 게임 내에서 생성되는 모든 아이템을 관리하는 DB
*/

#pragma once
#include <unordered_map>
#include "Inventory/Item/ItemBase.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	const ItemBase* GetItem(const std::string& id);
private:
	std::unordered_map<std::string, ItemBase*> m_itemDataBase;

	void LoadItemsFromFile(const std::string& filename);
	TargetStat StringToTargetStat(const std::string& str);
	ItemRank StringToItemRank(const std::string& str);
};