/*
인벤토리 구조체를 정의한 클래스입니다.
최대한 Player에게 Inventory 인스턴스를 하나만 가지도록 설계하였습니다.


*/

#pragma once
#include <vector>
#include <map>
#include "../Type/GameTypes.h"
#include "../Manager/ItemManager/ItemManager.h"

#define MAX_INVENTORY_SIZE 10
class ItemBase;


struct ItemSlot
{
public:
	ItemSlot() : m_item(nullptr), m_count(0) {}
	ItemSlot(const ItemBase* item, int count) : m_item(item), m_count(count) {}

	void AddCount(int amount) { m_count += amount; }
	// 아이템 차감 함수 필요

	const ItemBase* GetItem() const { return m_item; }
	int GetCount() const { return m_count; }
	bool IsEmpty() const { return m_item == nullptr; }
private:
	const ItemBase* m_item;
	int m_count;
};

class Inventory
{

public:
	Inventory();
	~Inventory();

	void AddItem(ItemID id, int amount = 1);
	void PrintItemList();
	const std::vector<ItemSlot>& GetItemSlots() const { return m_itemSlots; }

private:
	std::vector<ItemSlot> m_itemSlots;

	bool IsFull() const { return m_itemSlots.size() >= MAX_INVENTORY_SIZE; }
	int IsExist(ItemID id) const;

	// 아래 변수는 GameManager처럼 상위 매니저에서 가져와야 된다고 판단하나, 현재는 ItemManager에서 직접 가져오는 것으로 구현
	ItemManager itemManager;
	 
};