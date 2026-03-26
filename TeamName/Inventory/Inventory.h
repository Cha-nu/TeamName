#pragma once
#include <array>
#include <map>

#define MAX_INVENTORY_SIZE 10

struct ItemSlot
{
	ItemBase* item;
	int count;

	ItemSlot() : item(nullptr), count(0) {}

	bool IsEmpty() const { return item == nullptr; }
};

class ItemBase;
class Inventory
{

public:
	Inventory();
	~Inventory();

	void AddItem(ItemBase* item);
	void PrintItemList();

private:
	std::array<ItemSlot, MAX_INVENTORY_SIZE> m_itemSlots;

	bool IsFull() const { m_itemSlots.size() == m_itemSlots.max_size(); }
};