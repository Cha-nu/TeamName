#include <iostream>
#include "Inventory.h"
#include "Item/ItemBase.h"

Inventory::Inventory()
{
	m_itemSlots.reserve(MAX_INVENTORY_SIZE);
}

Inventory::~Inventory()
{
	
}

void Inventory::AddItem(const std::string& id , int amount)
{
	int index = IsExist(id);
	if (index != -1)
	{
		// 아이템 이미 있는지 없는지에 따라 로직을 분류
		m_itemSlots[index].AddCount(amount);
	}
	else
	{
		if (IsFull())
		{
			// 인벤토리가 가득 찼을 때 로직 처리
			return;
		}

		// 아이템이 존재하지 않는 경우 새로 추가
		const ItemBase* newItem = itemManager.GetItem(id);
		if (newItem)
		{
			m_itemSlots.push_back(ItemSlot(newItem, amount));
		}
		// 만약 newItem이 nullptr이면 아이템이 존재하지 않는 경우이므로, ItemManager에서 Item을 DB에 추가해야 합니다.
	}
}

void Inventory::RemoveItem(const std::string& id , int amount)
{
	int index = IsExist(id);
	if ( index != -1 )
	{
		m_itemSlots[index].RemoveCount(amount);
		if ( m_itemSlots[index].GetCount() <= 0 )
		{
			m_itemSlots.erase(m_itemSlots.begin() + index);
		}
	}
}

void Inventory::PrintItemList()
{

}

int Inventory::IsExist(const std::string& id) const
{
	for (int i = 0; i < static_cast<int>(m_itemSlots.size()); i++)
	{
		if (m_itemSlots[i].GetItem() && m_itemSlots[i].GetItem()->GetID() == id)
		{
			return i;
		}
	}

	return -1;
}
