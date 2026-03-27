#include <iostream>
#include <iomanip>
#include "Inventory.h"
#include "Item/ItemBase.h"
#include "Manager/ItemManager/ItemManager.h"

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
		const ItemBase* newItem = ItemManager::GetInstance().GetItem(id);
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
// 인벤토리 리스트를 순회하여 깔끔하게 보이도록 구성하긴 했으나, 출력 방식은 자유롭게 수정가능합니다.
void Inventory::PrintItemList()
{
	std::cout << "\n======================== [ 인벤토리 ] ========================\n";

	if ( m_itemSlots.empty() )
	{
		std::cout << "인벤토리가 비어 있습니다.\n";
		std::cout << "==============================================================\n";
		return;
	}

	// std::left는 왼쪽 정렬, std::setw는 출력 폭을 설정하는 함수입니다.
	std::cout << std::left
		<< std::setw(8) << "[번호]"
		<< std::setw(20) << "이름"
		<< std::setw(10) << "소지 개수"
		<< "설명\n";
	std::cout << "--------------------------------------------------------------\n";

	for (int i = 0; i < m_itemSlots.size(); i++)
	{
		const ItemSlot& slot = m_itemSlots[i];

		if ( slot.GetItem() != nullptr )
		{
			std::cout << "[" << std::right << std::setw(2) << (i + 1) << "]   ";

			// 이름, 개수, 설명 출력
			std::cout << std::left
				<< std::setw(17) << slot.GetItem()->GetName()
				<< std::right << std::setw(3) << slot.GetCount() << "개   "
				<< std::left << slot.GetItem()->GetDescription()
				<< "\n";
		}
	}
	std::cout << "==============================================================\n";
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
