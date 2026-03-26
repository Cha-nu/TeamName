#pragma once

#include "ItemBase.h"

class ConsumableItem : public ItemBase
{
public:
	ConsumableItem(const std::string& name, ItemRank rank, ItemID id, TargetStat stat, int amount, bool isDamage = false);
	virtual ~ConsumableItem();
	// virtual void Use() override;
private:
	TargetStat m_targetStat;
	int m_amount;
	bool m_isDamage;
};