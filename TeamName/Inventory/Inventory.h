/*
인벤토리 구조체를 정의한 클래스입니다.
최대한 Player에게 Inventory 인스턴스를 하나만 가지도록 설계하였습니다.


*/

#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include "Type/GameTypes.h"

#define MAX_INVENTORY_SIZE 10
class ItemBase;

struct ItemSlot
{
public:
	ItemSlot() : m_item(nullptr), m_count(0) {}
	ItemSlot(const ItemBase* item, int count) : m_item(item), m_count(count) {}

	void AddCount(int amount) { m_count += amount; }
	void RemoveCount(int amount = 1) { m_count = (std::max)(0, m_count - amount); }

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

	void AddItem(const std::string& id, int amount = 1);
	void RemoveItem(const std::string& id, int amount = 1);

	void PrintItemList();
	const std::vector<ItemSlot>& GetItemSlots() const { return m_itemSlots; }
	const ItemSlot& GetItemSlot(int index) const { return m_itemSlots.at(index); }

private:
	std::vector<ItemSlot> m_itemSlots;

	bool IsFull() const { return m_itemSlots.size() >= MAX_INVENTORY_SIZE; }

	// ID에 해당하는 아이템이 있는지 확인한 후, 있다면 해당 아이템의 인덱스를 반환, 없다면 -1 반환
	int IsExist(const std::string& id) const;
};