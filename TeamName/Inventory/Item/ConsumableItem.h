/*
 * 소모성 아이템을 정의하는 클래스입니다.
 *
 */


#pragma once

#include "ItemBase.h"

class ConsumableItem : public ItemBase
{
public:
	ConsumableItem(std::string id, const std::string& name, ItemRank rank, TargetStat stat, int amount, bool isDamage = false);
	virtual ~ConsumableItem();
	
	virtual void Use(Player& player) override;
	virtual void Use(Monster& target) override;
private:
	TargetStat m_targetStat;
	int m_amount;
	bool m_isDamage;
};