/*
* 게임 내에서 생성되는 모든 아이템을 관리하는 DB
*/

#pragma once
#include <unordered_map>
#include <string>
#include "Inventory/Item/ItemBase.h"
#include "Inventory/Item/ConsumableItem.h"


class ItemManager
{
public:
	~ItemManager()
	{
		for (auto& pair : m_itemDataBase)
		{
			delete pair.second;
		}
		m_itemDataBase.clear();
	}

	ItemManager()
	{
		// 모든 아이템을 여기에 등록
		// 예) m_itemDataBase[ItemID::HealthPotion_Common] = new ConsumableItem("일반 체력 포션", ItemRank::Common, ItemID::HealthPotion_Common, TargetStat::HP, 50);
	}

	const ItemBase* GetItem(const ItemID& id)
	{
		auto it = m_itemDataBase.find(id);
		if (it != m_itemDataBase.end())
		{
			return it->second;
		}
		else
		{
			return nullptr;
		}
	}

private:
	std::unordered_map<ItemID, ItemBase*> m_itemDataBase;
};